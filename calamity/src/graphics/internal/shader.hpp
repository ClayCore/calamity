#pragma once

#include "GL/glew.h"
#include "utils/hash/hash.hpp"
#include "zcommon.hpp"

namespace Calamity::GFX
{
    namespace Utils
    {
        class ShaderLoader
        {
          public:
            static Ref<Shader> load(const std::string& path);

            inline static void set_filepath(const std::string& path)
            {
                s_shader_filepath = path;
            }

          private:
            static std::string s_shader_filepath;

            static std::unordered_map<usize, Ref<Shader>> s_shader_cache;
        };
    }  // namespace Utils

    class Shader
    {
        friend class Utils::ShaderLoader;

      private:
        // Utility typedefs           //
        // -------------------------- //
        using SourceMap = std::unordered_map<usize, std::string>;

        // Constructors           //
        // ---------------------- //
        Shader(const std::string& path);

        // Utility methods for           //
        // compiling shaders             //
        // ----------------------------- //
        void compile(const SourceMap& sources);

        static usize from_string(const std::string& type);

        // Preprocess the source code                //
        // to push a shader onto the cache           //
        // ----------------------------------------- //
        SourceMap preprocess_binary(std::string& source);

      public:
        ~Shader();

        // Enables a given shader           //
        // -------------------------------- //
        void bind() const;

        // Disables a given shader           //
        // --------------------------------- //
        void unbind() const;

        constexpr usize get_shader_id() const
        {
            return this->m_shader_id;
        }

        // Properties           //
        // -------------------- //
      private:
        usize m_shader_id;
        std::string m_shader_path;
    };

}  // namespace Calamity::GFX
