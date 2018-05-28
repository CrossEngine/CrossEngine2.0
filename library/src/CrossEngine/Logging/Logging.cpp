/**************************************************************
 * Program Title: CrossEngine
 * Filename: Logging.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Logging/Logging.hpp>

CrossEngine::Logging::SharedLogger CrossEngine::Logging::GetLogger(const CrossEngine::Util::Containers::String &name,
                                                                   const CrossEngine::Logging::SinksVector &sinks) {
    return CrossEngine::Util::Memory::Allocate<spdlog::logger>(name, sinks.begin(), sinks.end());
}
