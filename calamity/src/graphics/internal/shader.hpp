#pragma once

#include "types.hpp"
#include "zcommon.hpp"

namespace Calamity::GFX
{
    // Base virtual classes                 //
    // Derive for use with either           //
    // Vulkan or OpenGL shaders             //
    // ==================================== //
    namespace Utils
    {
        // Base shader class           //
        // =========================== //
        class Shader
        {
            public:
            // Destructors           //
            // --------------------- //
            virtual ~Shader() = default;

            // Shader functions           //
            // -------------------------- //
            virtual void
            bind() const = 0;

            virtual void
            unbind() const = 0;

            static Ref<Shader>
            create(const std::string& path);

            // Accessors and mutators           //
            // -------------------------------- //
            virtual const std::string&
            get_name() const = 0;
        };

        // Base shader library           //
        // ============================= //
        class ShaderLibrary
        {
            public:
            // Shader library functions           //
            // ---------------------------------- //
            void
            add(const std::string& name, const Ref<Shader>& shader);

            void
            add(const Ref<Shader>& shader);

            Ref<Shader>
            load(const std::string& path);

            Ref<Shader>
            load(const std::string& name, const std::string& path);

            // Accessors and mutators           //
            // -------------------------------- //
            Ref<Shader>
            get(const std::string& name);

            bool
            exists(const std::string& name) const;

            // Properties           //
            // -------------------- //
            private:
            std::unordered_map<std::string, Ref<Shader>> m_shaders;
        };
    } // namespace Utils

    // OpenGL Shader class           //
    // ============================= //
    class OpenGLShader : public Utils::Shader
    {
        public:
        // Constructors           //
        // ---------------------- //
        OpenGLShader(const std::string& path);

        OpenGLShader(const std::string& name, const std::string& vert_src,
                     const std::string& frag_src);
        virtual ~OpenGLShader();

        // Shader functions           //
        // -------------------------- //
        virtual void
        bind() const override;

        virtual void
        unbind() const override;

        virtual const std::string&
        get_name() const override
        {
            return m_name;
        }

        // Properties           //
        // -------------------- //
        private:
        std::string m_path;
        std::string m_name;
    };
} // namespace Calamity::GFX
