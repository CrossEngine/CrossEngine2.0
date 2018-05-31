/**************************************************************
 * Program Title: CrossEngine
 * Filename: EventBus.cpp
 * Author: Blake Rogan
 * Last modified: 29/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/EventBus/EventBus.hpp>
#include <iostream>

CrossEngine::EventBus::EventBus::EventBus(const CrossEngine::Util::String &name) {
    log = CrossEngine::Logging::GetLogger(name);
    log->info("Created Event Bus");
    parent = nullptr;
}

CrossEngine::EventBus::EventBus::EventBus(const CrossEngine::Util::String &name,
                                          const CrossEngine::EventBus::EventBus::SharedEventBus &parent)
        : CrossEngine::EventBus::EventBus(name) {
    this->parent = parent;
    this->parent->AddChildEventBus(this);
}

CrossEngine::EventBus::EventBus::~EventBus() {
    log->info("Destroyed Event Bus");
    if (this->parent) {
        this->parent->RemoveChildEventBus(this);
    }
}

void CrossEngine::EventBus::EventBus::AddChildEventBus(CrossEngine::EventBus::EventBus *child) {
    std::lock_guard<std::mutex> lock(childMutex);
    this->children.push_back(child);
}

void CrossEngine::EventBus::EventBus::RemoveChildEventBus(CrossEngine::EventBus::EventBus *child) {
    std::lock_guard<std::mutex> lock(childMutex);
    auto ret = std::remove(this->children.begin(), this->children.end(), child);
}

void CrossEngine::EventBus::EventBus::Pulse() {
    auto event = PopEvent();
    if (event) {
        std::lock_guard<std::mutex> lock(handlerMutex);

        auto it = eventHandlers.find(event->GetID());
        if (it == eventHandlers.end()) {
            if (parent) {
                parent->Publish(event);
            }
        } else {
            log->info("Attempt to handle event: {}", event->GetID().hash);
            for (const auto &handler : (*it).second) {
                handler->Callback(event->GetSharedEvent());
            }
        }
    }
}

void
CrossEngine::EventBus::EventBus::Publish(const CrossEngine::EventBus::EventContainer::SharedEventContainer &event) {
    log->info("Publish Event: {} {}", event->GetID().hash, event->GetID().mangled);
    {
        std::lock_guard<std::mutex> guard(eventMutex);
        events.push(event);
    }
    eventCondition.notify_one();
}

CrossEngine::EventBus::EventHandlerID
CrossEngine::EventBus::EventBus::Subscribe(const CrossEngine::EventBus::BaseEvent::EventID &event,
                                           const CrossEngine::EventBus::BaseEventHandlerContainer::SharedEventHandler &handler) {
    std::lock_guard<std::mutex> lock(handlerMutex);
    auto it = eventHandlers.find(event);
    size_t index = 0;
    if (it == eventHandlers.end()) {
        EventHandlerSet set;
        auto inserted = set.insert(handler);
        index = static_cast<size_t>(std::distance(set.begin(), inserted.first));
        eventHandlers[event] = set;
    } else {
        auto inserted = (*it).second.insert(handler);
        index = static_cast<size_t>(std::distance((*it).second.begin(), inserted.first));
    }
    log->info("Subscribed Event Handler: {} {} {}", event.hash, handler->GetPriority(), index);
    return {index};
}

void CrossEngine::EventBus::EventBus::Unsubscribe(CrossEngine::EventBus::BaseEvent::EventID event,
                                                  CrossEngine::EventBus::EventHandlerID handlerID) {
    std::lock_guard<std::mutex> lock(handlerMutex);
    auto it = eventHandlers.find(event);
    if (it != eventHandlers.end()) {
        auto setIt = (*it).second.begin();
        std::advance(setIt, handlerID.index);
        (*it).second.erase(setIt);
        log->info("Unsubscribed EventHandler: {} {}", event.hash, handlerID.index);
    }
}

CrossEngine::EventBus::EventContainer::SharedEventContainer CrossEngine::EventBus::EventBus::PopEvent() {
    std::unique_lock<std::mutex> lock(eventMutex);
    if (eventCondition.wait_for(lock, std::chrono::milliseconds(1), [this]() { return !events.empty(); })) {
        auto event = events.top();
        events.pop();
        return event;
    }
    return nullptr;
}
