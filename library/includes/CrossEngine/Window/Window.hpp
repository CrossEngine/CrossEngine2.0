/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Window.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_WINDOW_HPP
#define CROSSENGINE_BUILDNUMBER_WINDOW_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Render/Renderer.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Window/WindowEvents.hpp>

#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#include <thread>
#include <atomic>

namespace CrossEngine {
    namespace Window {

        enum RenderAPI {
            API_OpenGL,
            API_OpenGLES,
            API_Vulkan,
        };

        class Window {
        private:
            GLFWwindow *window;
            GLFWwindow *resourceContext;

            EventBus::EventBus::SharedEventBus windowBus;
            Render::SharedRenderer renderer;

            std::atomic_bool isRendering;
            std::thread renderThread;

        public:
            CrossEngineAPI Window(
                    const Util::String &name,
                    int width,
                    int height,
                    RenderAPI api,
                    const EventBus::EventBus::SharedEventBus &eventBus,
                    const Render::SharedRenderer& renderer
            );

            CrossEngineAPI ~Window();

            CrossEngineAPI bool IsValid();

            CrossEngineAPI bool ShouldClose();

            CrossEngineAPI void Pulse();

            CrossEngineAPI void StartRenderLoop();

            CrossEngineAPI void StopRenderLoop();

        private:

            void PrivateRenderLoop();

        };

        typedef Util::Memory::Shared <Window> SharedWindow;
        typedef Util::Containers::Vector <SharedWindow> WindowVector;

        template<class ...Args>
        CrossEngineAPI SharedWindow CreateWindowT(Args...args) {
            return CrossEngine::Util::Memory::Allocate<Window>(args...);
        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_WINDOW_HPP
