/**************************************************************
 * Program Title: Hello World
 * Filename: HelloWorld.cpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description:
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include "HelloWorld.hpp"

CE_IMPLEMENT_APPLICATION(HelloWorld);

void HelloWorld::OnStartup() {
    log->info("Hello World");
    mainEventBus->Subscribe<ExampleEvent>(0, this);
    mainEventBus->Subscribe<ExampleEvent2>(0, this);
    mainEventBus->Subscribe<CrossEngine::Window::Events::MousePosEvent>(0, this);
    mainEventBus->Subscribe<CrossEngine::Window::Events::KeyEvent>(0, this);
    mainEventBus->Publish<ExampleEvent>(10);
    mainEventBus->Publish<ExampleEvent2>();
    window = windowManager->NewWindow("Example", 800, 600);

    Application::OnStartup();
}

void HelloWorld::OnShutdown() {
    log->info("Shutdown");
    window = nullptr;
    Application::OnShutdown();
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent> &event) {
    log->info("Hello World");
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent2> &event) {
    log->info("Hello World 2");
}

void
HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::MousePosEvent> &event) {
    log->info("On Mouse Move: {}x{}", event->GetX(), event->GetY());
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::KeyEvent> &event) {
    auto scan = glfwGetKeyName(event->GetKey(), event->GetScan());
    log->info(
            "On Key Press: {} {} {} {} {}",
            event->GetKey(), event->GetScan(), event->GetAction(),
            event->GetMods(), scan ? scan : ""

    );
}

ExampleEvent::ExampleEvent(int value) {
    aValue = value;
}

int ExampleEvent::GetValue() const {
    return aValue;
}
