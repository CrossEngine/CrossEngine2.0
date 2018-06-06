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

#include <CrossEngine/config.h>

#include <CrossEngine/Render/OpenGL/OpenGL.hpp>
#include <CrossEngine/Window/Window.hpp>

#include <CrossEngine/Render/Renderer.hpp>
#include <CrossEngine/Render/OpenGL/Model.hpp>
#include <CrossEngine/Render/OpenGL/Shader.hpp>
#include <CrossEngine/Render/OpenGL/Material.hpp>

namespace CrossEngine {
    namespace Render {
        /**
         *
         */
        class OpenGLRenderer: public Renderer {
        private:
        public:
            /**
             *
             */
            CrossEngineAPI OpenGLRenderer();

            /**
             *
             */
            CrossEngineAPI ~OpenGLRenderer();

            /**
             *
             * \param window
             * \return
             */
            CrossEngineAPI bool Setup(Window::Window* window) override;

            /**
             *
             * \param window
             * \param delta
             * \return
             */
            CrossEngineAPI bool Render(Window::Window* window, const Util::DeltaTime& delta) override;

            /**
             *
             * \param window
             * \return
             */
            CrossEngineAPI bool Teardown(Window::Window* window) override;

            /**
             *
             * \param name
             * \param source
             * \param type
             * \return
             */
            CrossEngineAPI SharedShaderSource LoadShaderSource(const Util::String& name, const Util::CharVector& source, GLenum type) override;

            /**
             *
             * \param sources
             * \return
             */
            CrossEngineAPI SharedShaderProgram LoadShaderProgram(const ShaderSourceVector& sources) override;

            /**
             *
             * \param object
             * \return
             */
            CrossEngineAPI Model* CompileRenderObject(RenderObject** object) override;
        };
    }
}


#endif //CROSSENGINE_BUILDNUMBER_OPENGLRENDERER_HPP
