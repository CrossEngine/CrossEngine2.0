/**************************************************************
 * Program Title: CrossEngine
 * Filename: Logging.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/Application/Application.hpp>

CrossEngine::Logging::SharedLogger CrossEngine::Logging::GetLogger(const CrossEngine::Util::String &name) {
    return GetLogger(
            name,
            GetApplication()->GetSinks()
    );
}

CrossEngine::Logging::SharedLogger CrossEngine::Logging::GetLogger(const CrossEngine::Util::Containers::String &name,
                                                                   const CrossEngine::Logging::SinksVector &sinks) {
    auto log = CrossEngine::Util::Memory::Allocate<spdlog::logger>(name, sinks.begin(), sinks.end());
    log->set_pattern("[%d/%m/%Y %H:%M:%S.%f] [%n] [%^%l%$] %v");
    return log;
}
