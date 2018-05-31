/**************************************************************
 * Program Title: Hello World
 * Filename: HelloWorld.hpp
 * Author: Blake Rogan
 * Last modified: 27/05/2018
 * Description:
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_HELLOWORLD_HPP
#define CROSSENGINE_HELLOWORLD_HPP

#include <iostream>
#include <CrossEngine.hpp>

class ExampleEvent: public CrossEngine::EventBus::Event<ExampleEvent> {
    int aValue;
public:
    ExampleEvent(int value);

    int GetValue() const;
};

class ExampleEvent2: public CrossEngine::EventBus::Event<ExampleEvent2> {

};

class HelloWorld: public CrossEngine::Application::Application, CrossEngine::EventBus::EventHandler<ExampleEvent, ExampleEvent2> {
public:

    void OnStartup() override;

    void OnShutdown() override;

    void HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent> &event);

    void HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent2> &event);

};

CE_DEFINE_APPLICATION(HelloWorld);


#endif //CROSSENGINE_HELLOWORLD_HPP
