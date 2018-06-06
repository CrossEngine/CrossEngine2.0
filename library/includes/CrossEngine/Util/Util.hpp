/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Util.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_UTIL_HPP
#define CROSSENGINE_BUILDNUMBER_UTIL_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Math.hpp>
#include <CrossEngine/Util/Clock.hpp>
#include <CrossEngine/Util/Memory.hpp>
#include <CrossEngine/Util/Containers.hpp>

#include <functional>


namespace CrossEngine {
    namespace Util {
        /**
         *
         */
        using String = Containers::String;

        /**
         *
         */
        typedef Util::Containers::Vector<String> StringVector;

        typedef Containers::Vector<char*> CharVector;

        /**
         *
         */
        using DeltaTime = Clock::DeltaTime;
    }
}


#endif //CROSSENGINE_BUILDNUMBER_UTIL_HPP
