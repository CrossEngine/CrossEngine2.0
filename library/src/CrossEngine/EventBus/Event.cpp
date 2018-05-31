/**************************************************************
 * Program Title: CrossEngine
 * Filename: Event.cpp
 * Author: Blake Rogan
 * Last modified: 30/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/EventBus/Event.hpp>

#include "CrossEngine/EventBus/Event.hpp"

bool CrossEngine::EventBus::operator==(const CrossEngine::EventBus::BaseEvent::EventID &lhs,
                                       const CrossEngine::EventBus::BaseEvent::EventID &rhs) {
    return lhs.hash == rhs.hash;
}

CrossEngine::EventBus::EventContainer::EventContainer(const CrossEngine::EventBus::BaseEvent::EventID& id,
                                                      const CrossEngine::EventBus::BaseEvent::SharedEvent &event) {
    this->id = id;
    this->event = event;
}

CrossEngine::EventBus::EventContainer::~EventContainer() {
    this->event = nullptr;
}

CrossEngine::EventBus::BaseEvent::EventID CrossEngine::EventBus::EventContainer::GetID() const {
    return id;
}

CrossEngine::EventBus::BaseEvent::SharedEvent CrossEngine::EventBus::EventContainer::GetSharedEvent() const {
    return event;
}

CrossEngine::EventBus::BaseEventHandlerContainer::BaseEventHandlerContainer(
        CrossEngine::EventBus::EventHandlerPriority priority,
        const CrossEngine::EventBus::BaseEvent::EventID& identifier) {
    this->priority = priority;
    this->identifier = identifier;
}

CrossEngine::EventBus::EventHandlerPriority
CrossEngine::EventBus::BaseEventHandlerContainer::GetPriority() const {
    return priority;
}

void CrossEngine::EventBus::BaseEventHandlerContainer::SetPriority(
        CrossEngine::EventBus::EventHandlerPriority priority) {
    this->priority = priority;
}

CrossEngine::EventBus::BaseEvent::EventID CrossEngine::EventBus::BaseEventHandlerContainer::GetIdentifier() const {
    return identifier;
}
