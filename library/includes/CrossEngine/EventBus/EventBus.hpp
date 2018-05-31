/**************************************************************
 * Program Title: CrossEngine
 * Filename: EventBus.hpp
 * Author: Blake Rogan
 * Last modified: 29/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_EVENTBUS_HPP
#define CROSSENGINE_BUILDNUMBER_EVENTBUS_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <CrossEngine/EventBus/Event.hpp>
#include <CrossEngine/EventBus/Events.hpp>
#include <CrossEngine/EventBus/EventHandler.hpp>

#include <thread>
#include <atomic>
#include <condition_variable>

namespace CrossEngine {
    namespace EventBus {
        class EventBus {
        public:
            typedef Util::Memory::Shared<EventBus> SharedEventBus;
            typedef Util::Containers::Vector<EventBus *> EventBusVector;

            typedef Util::Containers::Set<BaseEventHandlerContainer::SharedEventHandler> EventHandlerSet;
            typedef Util::Containers::UnorderedMap<BaseEvent::EventID, EventHandlerSet, EventHash> EventHandlerMap;
            typedef Util::Containers::PriorityQueue<EventContainer::SharedEventContainer> EventQueue;

        private:
            Logging::SharedLogger log;

            SharedEventBus parent;
            EventBusVector children;

            std::mutex childMutex;
            std::mutex handlerMutex;

            EventHandlerMap eventHandlers;

            EventQueue events;
            std::mutex eventMutex;
            std::condition_variable eventCondition;

        public:
            CrossEngineAPI explicit EventBus(const CrossEngine::Util::String &name);

            CrossEngineAPI EventBus(const CrossEngine::Util::String &name, const SharedEventBus &parent);

            CrossEngineAPI ~EventBus();

            CrossEngineAPI void AddChildEventBus(EventBus *child);

            CrossEngineAPI void RemoveChildEventBus(EventBus *child);

            CrossEngineAPI void Pulse();

            CrossEngineAPI void Publish(const EventContainer::SharedEventContainer &event);

            template<class EventType, class ...Args>
            CrossEngineAPI void Publish(Args...args) {
                CrossEngine::Util::Memory::Shared<EventType> event = CrossEngine::Util::Memory::Allocate<EventType>(
                        args...
                );

                CrossEngine::Util::Memory::Shared<EventContainer> container = CrossEngine::Util::Memory::Allocate<EventContainer>(
                        EventType::GetEventID(),
                        event
                );

                Publish(container);
            }

            CrossEngineAPI EventHandlerID Subscribe(const BaseEvent::EventID& event, const BaseEventHandlerContainer::SharedEventHandler &handler);

            template<class EventType, class EventHandlerType>
            CrossEngineAPI EventHandlerID Subscribe(EventHandlerPriority priority, EventHandlerType eventHandler) {
                BaseEventHandlerContainer::SharedEventHandler handler = Util::Memory::Allocate<EventHandlerContainer<EventType, EventHandlerType>>(
                        eventHandler, priority, EventType::GetEventID()
                );
                return Subscribe(EventType::GetEventID(), handler);
            }

            CrossEngineAPI void Unsubscribe(BaseEvent::EventID event, EventHandlerID handlerID);

            template<class EventType>
            CrossEngineAPI void Unsubscribe(EventHandlerID handlerID) {
                Unsubscribe(EventType::GetEventID(), handlerID);
            }

        private:

            EventContainer::SharedEventContainer PopEvent();

        };
    }
}


#endif //CROSSENGINE_BUILDNUMBER_EVENTBUS_HPP
