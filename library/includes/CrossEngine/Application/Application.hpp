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
#include <CrossEngine/Util/Memory.hpp>
#include <CrossEngine/Util/Containers.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <popl.hpp>

namespace CrossEngine {
    namespace Application {
        class Application {
        protected:
            Logging::SharedLogger log;

        public:

            CrossEngineAPI Application();

            CrossEngineAPI ~Application();

            CrossEngineAPI virtual Logging::SinksVector GetSinks();

            CrossEngineAPI virtual Util::Containers::String GetVendorLongName();

            CrossEngineAPI virtual Util::Containers::String GetVendorShortName();

            CrossEngineAPI virtual Util::Containers::String GetApplicationLongName();

            CrossEngineAPI virtual Util::Containers::String GetApplicationShortName();

            CrossEngineAPI int Entry(int argc, const char**argv);

            CrossEngineAPI virtual void Exit();

            CrossEngineAPI virtual int MainLoop();

            CrossEngineAPI virtual bool ParseCommandLine(int argc, const char** argv);

        };

        typedef Util::Memory::Shared<Application> SharedApplication;
    }
}

CrossEngineAPI CrossEngine::Application::SharedApplication GetApplication();

#define APPLICATION_MAIN_DEF(app) int main(int argc, const char** argv)

#define APPLICATION_GET_IMPL(app) static CrossEngine::Application::SharedApplication application = nullptr; CrossEngine::Application::SharedApplication GetApplication() {return application;}
#define APPLICATION_MAIN_IMPL(app) int main(int argc, const char** argv) {application = CrossEngine::Util::Memory::Allocate<app>(); return application->Entry(argc, argv);}

#define DEFINE_APPLICATION(app) APPLICATION_MAIN_DEF(app);
#define IMPLEMENT_APPLICATION(app) APPLICATION_GET_IMPL(app); APPLICATION_MAIN_IMPL(app);

#endif //CROSSENGINE_APPLICATION_HPP
