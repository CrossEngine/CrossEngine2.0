/**************************************************************
 * Program Title: CrossEngine
 * Filename: Application.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Application/Application.hpp>

#include <physfs.h>

CrossEngine::Application::Application::Application() {
}

CrossEngine::Application::Application::~Application() {

}

CrossEngine::Logging::SinksVector CrossEngine::Application::Application::GetSinks() {
    static CrossEngine::Logging::SinksVector sinks;
    if (sinks.empty()) {
        sinks.push_back(
#ifdef _WIN32
                std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>()
#else
                std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>()
#endif
        );
    }
    return sinks;
}

CrossEngine::Util::Containers::String CrossEngine::Application::Application::GetVendorLongName() {
    return "CrossEngine";
}

CrossEngine::Util::Containers::String CrossEngine::Application::Application::GetVendorShortName() {
    return "crossengine";
}

CrossEngine::Util::Containers::String CrossEngine::Application::Application::GetApplicationLongName() {
    return "Application";
}

CrossEngine::Util::Containers::String CrossEngine::Application::Application::GetApplicationShortName() {
    return "application";
}

int CrossEngine::Application::Application::Entry(int argc, const char **argv) {
    if (ParseCommandLine(argc, argv)) {
        PHYSFS_init(argv[0]);
        PHYSFS_setSaneConfig(GetVendorShortName().c_str(), GetApplicationShortName().c_str(), nullptr, 0, 0);

        log = CrossEngine::Logging::GetLogger("CrossEngine", GetSinks());
        log->info(
                "Initialised with CrossEngine version:"
        );

        log->info(
                "\tCompiled: {}.{}.{}-{}",
                CrossEngine_VERSION_MAJOR,
                CrossEngine_VERSION_MINOR,
                CrossEngine_VERSION_PATCH,
                CrossEngine_VERSION_BUILD
        );

        log->info(
                "\tLinked: {}.{}.{}-{}",
                GetVersionMajor(),
                GetVersionMinor(),
                GetVersionPatch(),
                GetVersionBuild()
        );
        log->info("Write Dir: {}", PHYSFS_getWriteDir());

        PHYSFS_mkdir("log");
        auto log = PHYSFS_openAppend("/log/test.log");
        PHYSFS_writeBytes(log, "Hello World", 11);
        PHYSFS_close(log);
        int r = MainLoop();
        Exit();
        PHYSFS_deinit();
        return r;
    }
    return 0;
}

void CrossEngine::Application::Application::Exit() {
    log->info("Shutting Application Down");
}

int CrossEngine::Application::Application::MainLoop() {
    return 0;
}

bool CrossEngine::Application::Application::ParseCommandLine(int argc, const char **argv) {
    auto parser = popl::OptionParser("CrossEngine Parser");
    auto help = parser.add<popl::Switch>("h", "help", "print this help message and exit");
    parser.parse(argc, const_cast<char **>(argv));
    if (help->is_set()) {
        if (help->value()) {
            std::cout << parser.help() << std::endl;
            return false;
        }
    }
    return true;
}
