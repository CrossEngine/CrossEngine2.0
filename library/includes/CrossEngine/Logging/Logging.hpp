/**************************************************************
 * Program Title: CrossEngine
 * Filename: Logging.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_LOGGING_HPP
#define CROSSENGINE_LOGGING_HPP

#include <CrossEngine/Util/Memory.hpp>
#include <CrossEngine/Util/Containers.hpp>

#include <spdlog/spdlog.h>

namespace CrossEngine {
    namespace Logging {

        typedef std::shared_ptr<spdlog::logger> SharedLogger;

        typedef Util::Containers::Vector<spdlog::sink_ptr> SinksVector;

        SharedLogger GetLogger(const Util::Containers::String& name);

        SharedLogger GetLogger(const Util::Containers::String& name, const SinksVector& sinks);

    }
}


#endif //CROSSENGINE_LOGGING_HPP
