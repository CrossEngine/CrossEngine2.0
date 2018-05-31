/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: WindowManager.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_WINDOWMANAGER_HPP
#define CROSSENGINE_BUILDNUMBER_WINDOWMANAGER_HPP


#include <CrossEngine/Render/OpenGLRenderer.hpp>
#include <CrossEngine/Render/Renderer.hpp>

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Window/Window.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>

namespace CrossEngine {
    namespace Window {
        class WindowManager {
        private:
            Logging::SharedLogger log;
            CrossEngine::EventBus::EventBus::SharedEventBus managerEventBus;
            WindowVector windows;

        public:
            CrossEngineAPI explicit WindowManager(const CrossEngine::EventBus::EventBus::SharedEventBus& eventBus);

            CrossEngineAPI ~WindowManager();

            template <class RendererType=Render::OpenGLRenderer>
            CrossEngineAPI SharedWindow NewWindow(const Util::String& name, int width, int height, RenderAPI api = API_OpenGL) {
                auto window = CrossEngine::Window::CreateWindowT(
                        name, width, height, api,
                        CrossEngine::EventBus::CreateEventBus(name, managerEventBus),
                        Util::Memory::Allocate<RendererType>()
                );
                window->StartRenderLoop();
                windows.push_back(window);
                return window;
            }

            CrossEngineAPI bool Pulse();
        };

        typedef Util::Memory::Shared<WindowManager> SharedWindowManager;

        template <class ...Args>
        CrossEngineAPI SharedWindowManager CreateWindowManager(Args...args) {
            return Util::Memory::Allocate<WindowManager>(args...);
        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_WINDOWMANAGER_HPP
