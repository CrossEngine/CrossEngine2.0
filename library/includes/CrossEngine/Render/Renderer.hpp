/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Renderer.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_RENDERER_HPP
#define CROSSENGINE_BUILDNUMBER_RENDERER_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Render/Shader.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Window/WindowEvents.hpp>
#include <CrossEngine/Render/RenderEvents.hpp>
#include <CrossEngine/Render/RenderObject.hpp>

//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//
//#include <thread>
//#include <atomic>

namespace CrossEngine {
    namespace Window {
        class Window;
    }

    namespace Render {

        /**
         *
         */
        typedef std::function<void(Window::Window*, const Util::DeltaTime&)> RenderFunction;

        /**
         *
         */
        typedef Util::Containers::List<RenderFunction> RenderFunctionVector;

        /**
         *
         */
        class Renderer: public EventBus::EventHandler<Events::PlayPauseEvent> {
        private:

        protected:
            Logging::SharedLogger log; /** */
            RenderFunctionVector renderFunctions; /** */

        public:
            /**
             *
             */
            CrossEngineAPI Renderer();

            /**
             *
             */
            CrossEngineAPI ~Renderer();

            /**
             *
             * \param window
             */
            CrossEngineAPI virtual void Create(Window::Window* window);

            /**
             *
             * \param window
             */
            CrossEngineAPI virtual void Destroy(Window::Window* window);

            /**
             *
             * \param window
             * \return
             */
            CrossEngineAPI virtual bool Setup(Window::Window* window);

            /**
             *
             * \param window
             * \param delta
             * \return
             */
            CrossEngineAPI virtual bool Render(Window::Window* window, const Util::DeltaTime& delta);

            /**
             *
             * \param window
             * \return
             */
            CrossEngineAPI virtual bool Teardown(Window::Window* window);

            /**
             *
             * \param event
             */
            CrossEngineAPI virtual void HandleEvent(const Events::SharedPlayPauseEvent& event);

            /**
             *
             * \param name
             * \param source
             * \param type
             * \return
             */
            CrossEngineAPI virtual SharedShaderSource LoadShaderSource(const Util::String& name, const Util::CharVector& source, GLenum type);

            /**
             *
             * \param sources
             * \return
             */
            CrossEngineAPI virtual SharedShaderProgram LoadShaderProgram(const ShaderSourceVector& sources);

            /**
             *
             * \param function
             */
            CrossEngineAPI void AddRenderFunction(const RenderFunction& function);

            /**
             *
             * \return
             */
            CrossEngineAPI virtual RenderObject* CreateRenderObject();

            /**
             *
             * \param object
             * \return
             */
            CrossEngineAPI virtual Model* CompileRenderObject(RenderObject** object) = 0;

        };

        /**
         *
         */
        typedef Util::Memory::Shared<Renderer> SharedRenderer;
    }
}


#endif //CROSSENGINE_BUILDNUMBER_RENDERER_HPP
