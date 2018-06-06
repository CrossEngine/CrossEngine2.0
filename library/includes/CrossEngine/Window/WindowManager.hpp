/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: WindowManager.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_WINDOWMANAGER_HPP
#define CROSSENGINE_WINDOWMANAGER_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Window/Window.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>

namespace CrossEngine {
    namespace Window {
        /**
         *
         */
        class WindowManager {
        private:
            Logging::SharedLogger log; /** */
            CrossEngine::EventBus::EventBus::SharedEventBus managerEventBus; /** */
            WindowVector windows; /** */

        public:
            /**
             *
             * \param eventBus
             */
            CrossEngineAPI explicit WindowManager(const CrossEngine::EventBus::EventBus::SharedEventBus& eventBus);

            /**
             *
             */
            CrossEngineAPI ~WindowManager();

            /**
             *
             * \tparam RendererType
             * \param name
             * \param width
             * \param height
             * \param api
             * \return
             */
            template <class RendererType>
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

            /**
             *
             * \return
             */
            CrossEngineAPI bool Pulse();
        };

        /**
         *
         */
        typedef Util::Memory::Shared<WindowManager> SharedWindowManager;

        /**
         *
         * \tparam Args
         * \param args
         * \return
         */
        template <class ...Args>
        CrossEngineAPI SharedWindowManager CreateWindowManager(Args...args) {
            return Util::Memory::Allocate<WindowManager>(args...);
        }
    }
}


#endif //CROSSENGINE_WINDOWMANAGER_HPP
