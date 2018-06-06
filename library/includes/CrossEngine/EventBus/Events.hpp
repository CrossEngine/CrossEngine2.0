/**************************************************************
 * Program Title: CrossEngine
 * Filename: Events.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_EVENTS_HPP
#define CROSSENGINE_EVENTS_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/EventBus/Event.hpp>

namespace CrossEngine {
    namespace EventBus {
        /**
         *
         */
        class ShutdownEvent : public CrossEngine::EventBus::Event<ShutdownEvent> {

        };

        /**
         *
         */
        typedef Util::Memory::Shared <ShutdownEvent> SharedShutdownEvent;
    }
}


#endif //CROSSENGINE_EVENTS_HPP
