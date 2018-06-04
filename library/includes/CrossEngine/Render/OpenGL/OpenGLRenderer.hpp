/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: OpenGLRenderer.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP
#define CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP

#include <glad/glad.h>

#include <CrossEngine/config.h>
#include <CrossEngine/Render/Renderer.hpp>

#include <CrossEngine/Render/OpenGL/Model.hpp>
#include <CrossEngine/Render/OpenGL/Shader.hpp>
#include <CrossEngine/Render/OpenGL/Material.hpp>

namespace CrossEngine {
    namespace Render {
        class OpenGLRenderer: public Renderer {
        private:

        public:
            CrossEngineAPI OpenGLRenderer();

            CrossEngineAPI ~OpenGLRenderer();

            CrossEngineAPI bool Setup(Window::Window* window) override;

            CrossEngineAPI bool Render(Window::Window* window, const Util::DeltaTime& delta) override;

            CrossEngineAPI bool Teardown(Window::Window* window) override;

            CrossEngineAPI SharedShaderSource LoadShaderSource(const Util::String& name, const Util::String& source, GLenum type) override;

            CrossEngineAPI SharedShaderProgram LoadShaderProgram(const ShaderSourceVector& sources) override;
        };
    }
}


#endif //CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP
