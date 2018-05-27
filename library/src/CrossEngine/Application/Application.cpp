/**************************************************************
 * Program Title: CrossEngine
 * Filename: Application.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Application/Application.hpp>

CrossEngine::Application::Application::Application() {
    log = CrossEngine::Logging::GetLogger("CrossEngine", GetSinks());
}

CrossEngine::Logging::SinksVector CrossEngine::Application::Application::GetSinks() {
    static CrossEngine::Logging::SinksVector sinks;
    if (sinks.empty()) {
        sinks.push_back(
                std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>()
        );
    }
    return sinks;
}

int CrossEngine::Application::Application::MainLoop(int argc, const char **argv) {
    return 0;
}
