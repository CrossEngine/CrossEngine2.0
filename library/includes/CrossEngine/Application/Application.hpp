/**************************************************************
 * Program Title: CrossEngine
 * Filename: Application.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_APPLICATION_HPP
#define CROSSENGINE_APPLICATION_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/IO/IOSystem.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>
#include <CrossEngine/Window/WindowManager.hpp>

#include <popl.hpp>
#include <atomic>

namespace CrossEngine {
    namespace Application {

        /**
         * Application Documentation
         */
        class Application : public EventBus::EventHandler<EventBus::ShutdownEvent> {
        private:
            Util::String applicationLongName; /** */
            Util::String applicationShortName; /** */
            Util::String vendorLongName; /** */
            Util::String vendorShortName; /** */

            std::atomic_bool running; /** */

        protected:
            Logging::SharedLogger log; /** */
            EventBus::EventBus::SharedEventBus mainEventBus; /** */
            IO::SharedIOSystem ioSystem; /** */
            Window::SharedWindowManager windowManager; /** */

        public:

            /**
             * Application Constructor
             */
            CrossEngineAPI Application();

            /**
             * Application Destructor
             */
            CrossEngineAPI ~Application();

            /**
             * Function to receive the available logging sinks
             * \return CrossEngine::Logging::SinksVector a vector of logging sinks
             */
            CrossEngineAPI virtual Logging::SinksVector GetSinks();

            /**
             *
             * \return
             */
            CrossEngineAPI Util::String GetVendorLongName() const;

            /**
             *
             * \param name
             */
            CrossEngineAPI void SetVendorLongName(const Util::String &name);

            /**
             *
             * \return
             */
            CrossEngineAPI Util::String GetVendorShortName() const;

            /**
             *
             * \param name
             */
            CrossEngineAPI void SetVendorShortName(const Util::String &name);

            /**
             *
             * \return
             */
            CrossEngineAPI Util::String GetApplicationLongName() const;

            /**
             *
             * \param name
             */
            CrossEngineAPI void SetApplicationLongName(const Util::String &name);

            /**
             *
             * \return
             */
            CrossEngineAPI Util::String GetApplicationShortName() const;

            /**
             *
             * \param name
             */
            CrossEngineAPI void SetApplicationShortName(const Util::String &name);

            /**
             *
             * \param argc
             * \param argv
             * \return
             */
            CrossEngineAPI virtual bool ParseCommandLine(int argc, const char **argv);

            /**
             *
             * \param argc
             * \param argv
             * \return
             */
            CrossEngineAPI int Entry(int argc, const char **argv);

            /**
             *
             */
            CrossEngineAPI virtual void OnStartup();

            /**
             *
             */
            CrossEngineAPI virtual void OnShutdown();

            /**
             *
             * \param errorCode
             * \param description
             */
            CrossEngineAPI void GLFWError(int errorCode, const char *description);

            /**
             *
             * \param event
             */
            CrossEngineAPI void HandleEvent(const EventBus::SharedShutdownEvent &event) override;

        private:
            /**
             *
             * \param argc
             * \param argv
             * \return
             */
            bool PrivateEntry(int argc, const char **argv);

            /**
             *
             * \return
             */
            int PrivateMainLoop();

            /**
             *
             */
            void PrivateExit();

        };

        /**
         *
         */
        typedef Util::Memory::Shared<Application> SharedApplication;

        /**
         *
         * \tparam ApplicationType
         * \tparam Args
         * \param args
         * \return
         */
        template<class ApplicationType, class ...Args>
        SharedApplication CreateApplication(Args...args) {
            return CrossEngine::Util::Memory::Allocate<ApplicationType>(args...);
        }
    }
}

/**
 *
 * \return
 */
CrossEngineAPI CrossEngine::Application::SharedApplication GetApplication();

/**
 *
 * \param newApplication
 * \return
 */
CrossEngineAPI CrossEngine::Application::SharedApplication
SetApplication(const CrossEngine::Application::SharedApplication &newApplication);

/**
 *
 */
#define APPLICATION_MAIN_DEF(app) int main(int argc, const char** argv)

/**
 *
 */
#define APPLICATION_MAIN_IMPL(app) int main(int argc, const char** argv) { \
                                       CrossEngine::Util::Clock::SetClock(CrossEngine::Util::Memory::Allocate<CrossEngine::Util::Clock::Clock>()); \
                                       CrossEngine::Application::SharedApplication application = CrossEngine::Application::CreateApplication<app>(); \
                                       SetApplication(application); \
                                       return application->Entry(argc, argv); \
                                   }

/**
*
*/
#define CE_DEFINE_APPLICATION(app) APPLICATION_MAIN_DEF(app);
/**
 *
 */
#define CE_IMPLEMENT_APPLICATION(app) APPLICATION_MAIN_IMPL(app);

#endif //CROSSENGINE_APPLICATION_HPP
