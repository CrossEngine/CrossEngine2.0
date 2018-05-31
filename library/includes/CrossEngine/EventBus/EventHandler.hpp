/**************************************************************
 * Program Title: CrossEngine
 * Filename: EventHandler.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_EVENTHANDLER_HPP
#define CROSSENGINE_BUILDNUMBER_EVENTHANDLER_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <thread>
#include <atomic>

namespace CrossEngine {
    namespace EventBus {

        typedef struct EventHandlerID {
            size_t index;
        } EventHandlerID;

        template <class EventType>
        class BaseEventHandler {
        public:
            CrossEngineAPI virtual typename EventType::EventID GetIdentifier() const {
                return EventType::GetEventID();
            }

            CrossEngineAPI virtual void HandleEvent(const CrossEngine::Util::Memory::Shared<EventType> &event) = 0;
        };

        template<class EventType, class ...EventTypes>
        class EventHandler: public BaseEventHandler<EventTypes>... {
        public:
            CrossEngineAPI virtual typename EventType::EventID GetIdentifier() const {
                return EventType::GetEventID();
            }

            CrossEngineAPI virtual void HandleEvent(const CrossEngine::Util::Memory::Shared<EventType> &event) = 0;
        };
    }
}


#endif //CROSSENGINE_BUILDNUMBER_EVENTHANDLER_HPP
