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

void HelloWorld::OnStartup(){
    log->info("Hello World");
    mainEventBus->Subscribe<ExampleEvent>(0, this);
    mainEventBus->Subscribe<ExampleEvent2>(0, this);
    mainEventBus->Publish<ExampleEvent>(10);
    mainEventBus->Publish<ExampleEvent2>();
    Application::OnStartup();
}

void HelloWorld::OnShutdown() {
    log->info("Shutdown");
    Application::OnShutdown();
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent> &event) {
    log->info("Hello World");
}

void HelloWorld::HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent2> &event) {
    log->info("Hello World 2");
}

ExampleEvent::ExampleEvent(int value) {
    aValue = value;
}

int ExampleEvent::GetValue() const {
    return aValue;
}
