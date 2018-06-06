/**************************************************************
 * Program Title: CrossEngine
 * Filename: EventBus.hpp
 * Author: Blake Rogan
 * Last modified: 29/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_EVENTBUS_HPP
#define CROSSENGINE_EVENTBUS_HPP

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
        /**
         *
         */
        class EventBus {
        public:
            /**
             *
             */
            typedef Util::Memory::Shared<EventBus> SharedEventBus;
            /**
             *
             */
            typedef Util::Containers::Vector<EventBus *> EventBusVector;

            /**
             *
             */
            typedef Util::Containers::Set<BaseEventHandlerContainer::SharedEventHandler> EventHandlerSet;
            /**
             *
             */
            typedef Util::Containers::UnorderedMap<BaseEvent::EventID, EventHandlerSet, EventHash> EventHandlerMap;
            /**
             *
             */
            typedef Util::Containers::PriorityQueue<EventContainer::SharedEventContainer> EventQueue;

        private:
            Logging::SharedLogger log; /** */

            SharedEventBus parent; /** */
            EventBusVector children; /** */

            std::mutex childMutex; /** */
            std::mutex handlerMutex; /** */

            EventHandlerMap eventHandlers; /** */

            EventQueue events; /** */
            std::mutex eventMutex; /** */
            std::condition_variable eventCondition; /** */

        public:
            /**
             *
             * \param name
             */
            CrossEngineAPI explicit EventBus(const CrossEngine::Util::String &name);

            /**
             *
             * \param name
             * \param parent
             */
            CrossEngineAPI EventBus(const CrossEngine::Util::String &name, const SharedEventBus &parent);

            /**
             *
             */
            CrossEngineAPI ~EventBus();

            /**
             *
             * \param child
             */
            CrossEngineAPI void AddChildEventBus(EventBus *child);

            /**
             *
             * \param child
             */
            CrossEngineAPI void RemoveChildEventBus(EventBus *child);

            /**
             *
             */
            CrossEngineAPI void Pulse();

            /**
             *
             * \param event
             */
            CrossEngineAPI void Publish(const EventContainer::SharedEventContainer &event);

            /**
             *
             * \tparam EventType
             * \tparam Args
             * \param args
             */
            template<class EventType, class ...Args>
            CrossEngineAPI void Publish(Args...args) {
                EventContainer::SharedEventContainer container = CreateEventContainer(
                        EventType::GetEventID(),
                        CreateEventT<EventType>(args...)
                );

                Publish(container);
            }

            /**
             *
             * \param event
             * \param handler
             * \return
             */
            CrossEngineAPI EventHandlerID Subscribe(const BaseEvent::EventID& event, const BaseEventHandlerContainer::SharedEventHandler &handler);

            /**
             *
             * \tparam EventType
             * \tparam EventHandlerType
             * \param priority
             * \param eventHandler
             * \return
             */
            template<class EventType, class EventHandlerType>
            CrossEngineAPI EventHandlerID Subscribe(EventHandlerPriority priority, EventHandlerType eventHandler) {
                BaseEventHandlerContainer::SharedEventHandler handler = CreateHandlerContainer<EventType, EventHandlerType>(
                        eventHandler, priority, EventType::GetEventID()
                );
                return Subscribe(EventType::GetEventID(), handler);
            }

            /**
             *
             * \param event
             * \param handlerID
             */
            CrossEngineAPI void Unsubscribe(BaseEvent::EventID event, EventHandlerID handlerID);

            /**
             *
             * \tparam EventType
             * \param handlerID
             */
            template<class EventType>
            CrossEngineAPI void Unsubscribe(EventHandlerID handlerID) {
                Unsubscribe(EventType::GetEventID(), handlerID);
            }

        private:

            /**
             *
             * \return
             */
            EventContainer::SharedEventContainer PopEvent();

        };


        /**
         *
         * \tparam Args
         * \param args
         * \return
         */
        template <class ...Args>
        CrossEngineAPI EventBus::SharedEventBus CreateEventBus(Args...args) {
            return Util::Memory::Allocate<EventBus>(args...);
        }
    }
}


#endif //CROSSENGINE_EVENTBUS_HPP
