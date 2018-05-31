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
#include <GLFW/glfw3.h>


static CrossEngine::Application::SharedApplication application = nullptr;

CrossEngine::Application::SharedApplication GetApplication() {
    return application;
}

CrossEngine::Application::SharedApplication
SetApplication(const CrossEngine::Application::SharedApplication &newApplication) {
    CrossEngine::Application::SharedApplication old = application;
    application = newApplication;
    return old;
}

static inline void GLFWErrorCallback(int errorCode, const char *description) {
    GetApplication()->GLFWError(errorCode, description);
}

CrossEngine::Application::Application::Application() : mainEventBus(nullptr) {
    applicationLongName = "Application";
    applicationShortName = "application";
    vendorLongName = "CrossEngine";
    vendorShortName = "crossengine";
}

CrossEngine::Application::Application::~Application() {
    PHYSFS_deinit();
}

CrossEngine::Logging::SinksVector CrossEngine::Application::Application::GetSinks() {
    static CrossEngine::Logging::SinksVector sinks;
    if (sinks.empty()) {
        PHYSFS_mkdir("log");
        sinks.push_back(
#ifdef _WIN32
                std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>()
#else
                std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>()
#endif
        );
        auto logPath = ioSystem->GetWriteDir() + "log" + PHYSFS_getDirSeparator() + "output.log";
        sinks.push_back(
                std::make_shared<spdlog::sinks::daily_file_sink_mt>(
                        logPath.c_str(), 0, 0
                )
        );
    }
    return sinks;
}

CrossEngine::Util::String CrossEngine::Application::Application::GetVendorLongName() const {
    return vendorLongName;
}

void CrossEngine::Application::Application::SetVendorLongName(const CrossEngine::Util::String &name) {
    vendorLongName = name;
}

CrossEngine::Util::String CrossEngine::Application::Application::GetVendorShortName() const {
    return vendorShortName;
}

void CrossEngine::Application::Application::SetVendorShortName(const CrossEngine::Util::String &name) {
    vendorShortName = name;
}

CrossEngine::Util::String CrossEngine::Application::Application::GetApplicationLongName() const {
    return applicationLongName;
}

void CrossEngine::Application::Application::SetApplicationLongName(const CrossEngine::Util::String &name) {
    applicationLongName = name;
}

CrossEngine::Util::String CrossEngine::Application::Application::GetApplicationShortName() const {
    return applicationShortName;
}

void CrossEngine::Application::Application::SetApplicationShortName(const CrossEngine::Util::String &name) {
    applicationShortName = name;
}

bool CrossEngine::Application::Application::ParseCommandLine(int argc, const char **argv) {
    auto parser = popl::OptionParser(GetApplicationLongName() + ":");
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

int CrossEngine::Application::Application::Entry(int argc, const char **argv) {
    if (PrivateEntry(argc, argv)) {
        OnStartup();
        int exitCode = PrivateMainLoop();
        OnShutdown();
        PrivateExit();
        return exitCode;
    }
    return -1;
}

void CrossEngine::Application::Application::OnStartup() {

}

void CrossEngine::Application::Application::OnShutdown() {

}

bool CrossEngine::Application::Application::PrivateEntry(int argc, const char **argv) {
    if (ParseCommandLine(argc, argv)) {
        ioSystem = CrossEngine::IO::CreateIOSystem(argv[0]);

        log = CrossEngine::Logging::GetLogger("CrossEngine", GetSinks());

        log->info(
                "Initialised with:"
        );

        log->info("\tCrossEngine version:");
        log->info(
                "\t\tCompiled: {}.{}.{}-{}",
                CrossEngine_VERSION_MAJOR,
                CrossEngine_VERSION_MINOR,
                CrossEngine_VERSION_PATCH,
                CrossEngine_VERSION_BUILD
        );
        log->info(
                "\t\tLinked: {}.{}.{}-{}",
                GetVersionMajor(),
                GetVersionMinor(),
                GetVersionPatch(),
                GetVersionBuild()
        );

        log->info("\tGLFW version:");
        log->info(
                "\t\tCompiled: {}.{}.{}",
                GLFW_VERSION_MAJOR,
                GLFW_VERSION_MINOR,
                GLFW_VERSION_REVISION
        );
        log->info(
                "\t\tLinked: {}",
                glfwGetVersionString()
        );

        log->info("\tPhysicsFS Version:");
        PHYSFS_Version version;
        PHYSFS_VERSION(&version);
        log->info(
                "\t\tCompiled: {}.{}.{}",
                version.major,
                version.minor,
                version.patch
        );
        PHYSFS_getLinkedVersion(&version);
        log->info(
                "\t\tLinked: {}.{}.{}",
                version.major,
                version.minor,
                version.patch
        );

        log->info("\tPOPL Version:");
        log->info("\t\tCompiled: {}", POPL_VERSION);

        log->info("\tspdlog Version:");
        log->info("\t\tCompiled: {}", SPDLOG_VERSION);

        mainEventBus = CrossEngine::EventBus::CreateEventBus("MainEventBus");
        mainEventBus->Subscribe<CrossEngine::EventBus::ShutdownEvent>(0, this);
        windowManager = CrossEngine::Window::CreateWindowManager(
                CrossEngine::EventBus::CreateEventBus("WindowManagerEventBus", mainEventBus)
        );

        auto file = ioSystem->Open("test.txt", IO::Open_Append);
        file->Write("Hello World", 11);

        glfwSetErrorCallback(GLFWErrorCallback);
        return glfwInit() == GLFW_TRUE;
    }
    return false;
}

int CrossEngine::Application::Application::PrivateMainLoop() {
    running = true;

    while (running) {
        bool r = windowManager->Pulse();
        if (r) {
            running = false;
        }
        mainEventBus->Pulse();
    }


    return 0;
}

void CrossEngine::Application::Application::PrivateExit() {
    mainEventBus = nullptr;
    glfwTerminate();
    log->info("Application Shutdown");
}


void CrossEngine::Application::Application::GLFWError(int errorCode, const char *description) {
    log->error("GLFW Error: {}: {}", errorCode, description);
}

void CrossEngine::Application::Application::HandleEvent(const CrossEngine::EventBus::SharedShutdownEvent &event) {
    log->info("Handled shutdown event");
    running = false;
}
