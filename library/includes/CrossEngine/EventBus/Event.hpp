/**************************************************************
 * Program Title: CrossEngine
 * Filename: Event.hpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_EVENT_HPP
#define CROSSENGINE_BUILDNUMBER_EVENT_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/Logging/Logging.hpp>

#include <thread>
#include <atomic>
#include <typeinfo>

namespace CrossEngine {
    namespace EventBus {

        typedef unsigned short EventHandlerPriority;

        class BaseEvent {
        public:
            typedef CrossEngine::Util::Memory::Shared<BaseEvent> SharedEvent;
            typedef struct EventID {
                size_t hash;
                Util::String mangled;
            } EventID;
        };


        typedef struct EventHash {
            CrossEngineAPI size_t operator () (const BaseEvent::EventID id) const noexcept {
                return id.hash;
            }
        } EventHash;

        CrossEngineAPI bool operator==(const BaseEvent::EventID& lhs, const BaseEvent::EventID& rhs);

        template <class EventType>
        class Event: public BaseEvent {
        public:
            CrossEngineAPI static EventID GetEventID() {
                EventID id;
                id.hash = typeid(EventType).hash_code();
                id.mangled = typeid(EventType).name();
                return id;
            }

        };

        class EventContainer {
        public:
            typedef CrossEngine::Util::Memory::Shared<EventContainer> SharedEventContainer;

        private:
            BaseEvent::EventID id;
            BaseEvent::SharedEvent event;

        public:
            CrossEngineAPI EventContainer(const BaseEvent::EventID& id, const BaseEvent::SharedEvent& event);

            CrossEngineAPI ~EventContainer();

            CrossEngineAPI BaseEvent::EventID GetID() const;

            CrossEngineAPI BaseEvent::SharedEvent GetSharedEvent() const;
        };

        class BaseEventHandlerContainer {
        public:
            typedef Util::Memory::Shared<BaseEventHandlerContainer> SharedEventHandler;
        private:
            EventHandlerPriority priority;
            BaseEvent::EventID identifier;
        public:
            CrossEngineAPI BaseEventHandlerContainer(EventHandlerPriority priority, const BaseEvent::EventID& identifier);

            CrossEngineAPI EventHandlerPriority GetPriority() const;

            CrossEngineAPI void SetPriority(EventHandlerPriority priority);

            CrossEngineAPI BaseEvent::EventID GetIdentifier() const;

            CrossEngineAPI virtual void Callback(const BaseEvent::SharedEvent& event) = 0;
        };

        template<class EventType, class EventHandlerType>
        class EventHandlerContainer : public BaseEventHandlerContainer {
        private:
            EventHandlerType eventHandler;
        public:
            CrossEngineAPI EventHandlerContainer(
                    const EventHandlerType& handler,
                    EventHandlerPriority priority,
                    const BaseEvent::EventID& identifier
            ) : BaseEventHandlerContainer(priority, identifier) {
                this->eventHandler = handler;
            }

            CrossEngineAPI ~EventHandlerContainer() {
                this->eventHandler = nullptr;
            }

            CrossEngineAPI void Callback(const BaseEvent::SharedEvent& event) override {
                this->eventHandler->HandleEvent(
                        std::static_pointer_cast<EventType>(event)
                );
            }
        };

        template <class EventType, class ...Args>
        CrossEngineAPI Util::Memory::Shared<EventType> CreateEventT(Args...args) {
            return Util::Memory::Allocate<EventType>(args...);
        }

        template <class ...Args>
        CrossEngineAPI EventContainer::SharedEventContainer CreateEventContainer(Args...args) {
            return Util::Memory::Allocate<EventContainer>(args...);
        }

        template <class EventType, class EventHandlerType, class ...Args>
        CrossEngineAPI BaseEventHandlerContainer::SharedEventHandler CreateHandlerContainer(Args...args) {
            return Util::Memory::Allocate<EventHandlerContainer<EventType, EventHandlerType>>(args...);
        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_EVENT_HPP
