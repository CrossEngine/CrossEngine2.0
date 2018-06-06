/**************************************************************
 * Program Title: CrossEngine
 * Filename: Event.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_EVENT_HPP
#define CROSSENGINE_EVENT_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <thread>
#include <atomic>
#include <typeinfo>

namespace CrossEngine {
    namespace EventBus {

        /**
         *
         */
        typedef unsigned short EventHandlerPriority;

        /**
         *
         */
        class BaseEvent {
        public:
            /**
             *
             */
            typedef CrossEngine::Util::Memory::Shared<BaseEvent> SharedEvent;

            /**
             *
             */
            typedef struct EventID {
                size_t hash; /** */
                Util::String mangled; /** */
            } EventID;
        };


        /**
         *
         */
        typedef struct EventHash {
            /**
             *
             * \param id
             * \return
             */
            CrossEngineAPI size_t operator () (const BaseEvent::EventID id) const noexcept {
                return id.hash;
            }
        } EventHash;

        /**
         *
         * \param lhs
         * \param rhs
         * \return
         */
        CrossEngineAPI bool operator==(const BaseEvent::EventID& lhs, const BaseEvent::EventID& rhs);

        /**
         *
         * \tparam EventType
         */
        template <class EventType>
        class Event: public BaseEvent {
        public:
            /**
             *
             * \return
             */
            CrossEngineAPI static EventID GetEventID() {
                EventID id;
                id.hash = typeid(EventType).hash_code();
                id.mangled = typeid(EventType).name();
                return id;
            }

        };

        /**
         *
         */
        class EventContainer {
        public:
            /**
             *
             */
            typedef CrossEngine::Util::Memory::Shared<EventContainer> SharedEventContainer;

        private:
            BaseEvent::EventID id; /** */
            BaseEvent::SharedEvent event; /** */

        public:
            /**
             *
             * \param id
             * \param event
             */
            CrossEngineAPI EventContainer(const BaseEvent::EventID& id, const BaseEvent::SharedEvent& event);

            /**
             *
             */
            CrossEngineAPI ~EventContainer();

            /**
             *
             * \return
             */
            CrossEngineAPI BaseEvent::EventID GetID() const;

            /**
             *
             * \return
             */
            CrossEngineAPI BaseEvent::SharedEvent GetSharedEvent() const;
        };

        /*
         *
         */
        class BaseEventHandlerContainer {
        public:
            /**
             *
             */
            typedef Util::Memory::Shared<BaseEventHandlerContainer> SharedEventHandler;
        private:
            EventHandlerPriority priority; /** */
            BaseEvent::EventID identifier; /** */
        public:
            /**
             *
             * \param priority
             * \param identifier
             */
            CrossEngineAPI BaseEventHandlerContainer(EventHandlerPriority priority, const BaseEvent::EventID& identifier);

            /**
             *
             * \return
             */
            CrossEngineAPI EventHandlerPriority GetPriority() const;

            /**
             *
             * \param priority
             */
            CrossEngineAPI void SetPriority(EventHandlerPriority priority);

            /**
             *
             * \return
             */
            CrossEngineAPI BaseEvent::EventID GetIdentifier() const;

            /**
             *
             * \param event
             */
            CrossEngineAPI virtual void Callback(const BaseEvent::SharedEvent& event) = 0;
        };

        /**
         *
         * \tparam EventType
         * \tparam EventHandlerType
         */
        template<class EventType, class EventHandlerType>
        class EventHandlerContainer : public BaseEventHandlerContainer {
        private:
            EventHandlerType eventHandler; /** */
        public:
            /**
             *
             * \param handler
             * \param priority
             * \param identifier
             */
            CrossEngineAPI EventHandlerContainer(
                    const EventHandlerType& handler,
                    EventHandlerPriority priority,
                    const BaseEvent::EventID& identifier
            ) : BaseEventHandlerContainer(priority, identifier) {
                this->eventHandler = handler;
            }

            /**
             *
             */
            CrossEngineAPI ~EventHandlerContainer() {
                this->eventHandler = nullptr;
            }

            /**
             *
             * \param event
             */
            CrossEngineAPI void Callback(const BaseEvent::SharedEvent& event) override {
                this->eventHandler->HandleEvent(
                        std::static_pointer_cast<EventType>(event)
                );
            }
        };

        /**
         *
         * \tparam EventType
         * \tparam Args
         * \param args
         * \return
         */
        template <class EventType, class ...Args>
        CrossEngineAPI Util::Memory::Shared<EventType> CreateEventT(Args...args) {
            return Util::Memory::Allocate<EventType>(args...);
        }

        /**
         *
         * \tparam Args
         * \param args
         * \return
         */
        template <class ...Args>
        CrossEngineAPI EventContainer::SharedEventContainer CreateEventContainer(Args...args) {
            return Util::Memory::Allocate<EventContainer>(args...);
        }

        /**
         *
         * \tparam EventType
         * \tparam EventHandlerType
         * \tparam Args
         * \param args
         * \return
         */
        template <class EventType, class EventHandlerType, class ...Args>
        CrossEngineAPI BaseEventHandlerContainer::SharedEventHandler CreateHandlerContainer(Args...args) {
            return Util::Memory::Allocate<EventHandlerContainer<EventType, EventHandlerType>>(args...);
        }
    }
}


#endif //CROSSENGINE_EVENT_HPP
