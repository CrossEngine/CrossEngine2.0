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

#include <popl.hpp>
#include <atomic>

namespace CrossEngine {
    namespace Application {

        class Application: public EventBus::EventHandler<EventBus::ShutdownEvent> {
        private:
            Util::String applicationLongName;
            Util::String applicationShortName;
            Util::String vendorLongName;
            Util::String vendorShortName;

            std::atomic_bool running;

        protected:
            Logging::SharedLogger log;
            EventBus::EventBus::SharedEventBus mainEventBus;
            IO::SharedIOSystem ioSystem;

        public:

            CrossEngineAPI Application();

            CrossEngineAPI ~Application();

            CrossEngineAPI virtual Logging::SinksVector GetSinks();

            CrossEngineAPI Util::String GetVendorLongName() const;

            CrossEngineAPI void SetVendorLongName(const Util::String &name);

            CrossEngineAPI Util::String GetVendorShortName() const;

            CrossEngineAPI void SetVendorShortName(const Util::String &name);

            CrossEngineAPI Util::String GetApplicationLongName() const;

            CrossEngineAPI void SetApplicationLongName(const Util::String &name);

            CrossEngineAPI Util::String GetApplicationShortName() const;

            CrossEngineAPI void SetApplicationShortName(const Util::String &name);

            CrossEngineAPI virtual bool ParseCommandLine(int argc, const char **argv);

            CrossEngineAPI int Entry(int argc, const char **argv);

            CrossEngineAPI virtual void OnStartup();

            CrossEngineAPI virtual void OnShutdown();

            CrossEngineAPI void GLFWError(int errorCode, const char *description);

            CrossEngineAPI void HandleEvent(const EventBus::SharedShutdownEvent& event) override;

        private:
            bool PrivateEntry(int argc, const char **argv);

            int PrivateMainLoop();

            void PrivateExit();

        };

        typedef Util::Memory::Shared<Application> SharedApplication;
    }
}

CrossEngineAPI CrossEngine::Application::SharedApplication GetApplication();

CrossEngineAPI CrossEngine::Application::SharedApplication
SetApplication(const CrossEngine::Application::SharedApplication &newApplication);

#define APPLICATION_MAIN_DEF(app) int main(int argc, const char** argv)

#define APPLICATION_MAIN_IMPL(app) int main(int argc, const char** argv) {\
                                       CrossEngine::Application::SharedApplication application = CrossEngine::Util::Memory::Allocate<app>(); \
                                       SetApplication(application); \
                                       return application->Entry(argc, argv);\
                                   }

#define CE_DEFINE_APPLICATION(app) APPLICATION_MAIN_DEF(app);
#define CE_IMPLEMENT_APPLICATION(app) APPLICATION_MAIN_IMPL(app);

#endif //CROSSENGINE_APPLICATION_HPP
