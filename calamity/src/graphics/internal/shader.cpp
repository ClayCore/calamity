#include "shader.hpp"

namespace Calamity::GFX
{
    namespace Utils
    {
        // Static declarations           //
        // ----------------------------- //
        std::string ShaderLoader::s_shader_filepath;

        std::unordered_map<usize, Ref<Shader>> ShaderLoader::s_shader_cache;

        // Loads a given shader from the cache           //
        // if the shader does not exist,                 //
        // loads it into the cache first.                //
        // --------------------------------------------- //
        Ref<Shader> ShaderLoader::load(const std::string& path)
        {
            // Acquire path to the shader source
            std::string shader_path = ShaderLoader::s_shader_filepath + path;

            usize hash = H_GetHash(shader_path);

            // Check cache for existing shaders
            auto it = ShaderLoader::s_shader_cache.find(hash);
            if (it != ShaderLoader::s_shader_cache.end()) { return it->second; }

            // Load the shader if none found
            Ref<Shader> shader = CreateRef<Shader>(shader_path);

            // Insert new shader
            ShaderLoader::s_shader_cache.insert(std::make_pair(hash, shader));

            return ShaderLoader::s_shader_cache[hash];
        }
    }  // namespace Utils

    Shader::Shader(const std::string& path)
    {
        this->m_shader_path = path;
    }

    Shader::~Shader()
    {
        glDeleteProgram(this->m_shader_id);
    }

    void Shader::compile(const SourceMap& sources)
    {
        this->m_shader_id = glCreateProgram();

        for (auto& item : sources) {
            usize type                = item.first;
            const std::string& source = item.second;

            // Create and compile shader
            u32 shader         = glCreateShader(type);
            auto shader_source = source.c_str();
            glShaderSource(shader, 1, &shader_source, nullptr);
            glCompileShader(shader);

            // Attach it to the shader id
            glAttachShader(this->m_shader_id, shader);
            glDeleteShader(shader);

            // Check the state of the shader
            i32 compile_return_code = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_return_code);
            if (compile_return_code == GL_FALSE || source.empty()) {
                i32 length;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

                // Error present, output to stderr
                // TODO: logging
                if (length > 0) {
                    std::vector<char> error(length);
                    glGetShaderInfoLog(shader, length, &length, &error[0]);
                    std::string err(error.begin(), error.end());

                    std::cerr << "compile error: " << m_shader_path << " " << err << "\n";
                } else {
                    std::cerr << "unknown compile error\n";
                }

                glDeleteShader(shader);
                break;
            }

            glAttachShader(this->m_shader_id, shader);
            glDeleteShader(shader);
        }

        glLinkProgram(this->m_shader_id);
        glValidateProgram(this->m_shader_id);
    }

    usize Shader::from_string(const std::string& type)
    {
        auto result = 0;

        switch (H_GetHash(type)) {
            case "vertex"_hash: {
                result = GL_VERTEX_SHADER;
            } break;
            case "fragment"_hash: {
                result = GL_FRAGMENT_SHADER;
            } break;
            case "geometry"_hash: {
                result = GL_GEOMETRY_SHADER;
            } break;
            case "hull"_hash: {
                result = GL_TESS_CONTROL_SHADER;
            } break;
            case "domain"_hash: {
                result = GL_TESS_EVALUATION_SHADER;
            } break;
            case "compute"_hash: {
                result = GL_COMPUTE_SHADER;
            } break;
            default: {
                // TODO: logging
                std::cerr << "Unknown shader type" << std::endl;
            } break;
        }

        return result;
    }

    auto Shader::preprocess_binary(std::string& source) -> SourceMap
    {
        auto check_type = [&](const std::string& str) constexpr
        {
            switch (H_GetHash(str)) {
                case "vertex"_hash: [[fallthrough]];
                case "fragment"_hash: [[fallthrough]];
                case "geometry"_hash: [[fallthrough]];
                case "hull"_hash: [[fallthrough]];
                case "domain"_hash: [[fallthrough]];
                case "compute"_hash: {
                    return true;
                } break;
                default: {
                    std::cerr << "unrecognized shader type\n";
                    return false;
                }
            }
        };

        SourceMap shader_sources;

        // Begin tokenization
        auto type_token = "#shader_type";
        usize token_len = std::strlen(type_token);
        usize offset    = source.find(type_token);

        while (offset != std::string::npos) {
            // Calculate all the necessary offsets to find the data
            usize eol = source.find_first_of("\r\n", offset);

            // Check for syntax errors in shaders
            if (eol == std::string::npos) {
                // TODO: Logging and cleanup
                std::cerr << "syntax error in shader: " << this->m_shader_path << "\n";
            }

            usize start      = offset + token_len + 1;
            std::string type = source.substr(start, eol - start);

            if (check_type(type)) {
                usize next_line = source.find_first_not_of("\r\n", eol);
                offset          = source.find(type_token, next_line);

                auto acquire_data = [&]() {
                    if (next_line == std::string::npos) {
                        return source.size() - 1;
                    } else {
                        return next_line;
                    }
                };

                // Append shader data to the sources of a distinct type
                shader_sources[from_string(type)] = source.substr(next_line, offset - acquire_data());
            }
        }
    }

    void Shader::bind() const
    {
        glUseProgram(this->m_shader_id);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }
}  // namespace Calamity::GFX
