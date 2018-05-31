/**************************************************************
 * Program Title: CrossEngine
 * Filename: IOSystem.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_IOSYSTEM_HPP
#define CROSSENGINE_BUILDNUMBER_IOSYSTEM_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/IO/IOFile.hpp>
#include <CrossEngine/IO/IOStream.hpp>
#include <CrossEngine/Logging/Logging.hpp>
#include <CrossEngine/EventBus/EventBus.hpp>

namespace CrossEngine {
    namespace IO {
        class IOSystem {
        private:
            Logging::SharedLogger log;
        public:
            CrossEngineAPI explicit IOSystem(const char* init);

            CrossEngineAPI ~IOSystem();

            CrossEngineAPI Util::String GetWriteDir() const;

            CrossEngineAPI bool Exists(const Util::String& filename);

            CrossEngineAPI SharedIOFile Open(const Util::String& filename, OpenMode mode);
        };

        typedef Util::Memory::Shared<IOSystem> SharedIOSystem;


        template <class ...Args>
        CrossEngineAPI SharedIOSystem CreateIOSystem(Args...args) {
            return Util::Memory::Allocate<IOSystem>(args...);
        }

    }
}


#endif //CROSSENGINE_BUILDNUMBER_IOSYSTEM_HPP
