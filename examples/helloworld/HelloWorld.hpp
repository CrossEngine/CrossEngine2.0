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

/**
 *
 */
class ExampleEvent : public CrossEngine::EventBus::Event<ExampleEvent> {
    int aValue; /** */
public:
    /**
     *
     * \param value
     */
    ExampleEvent(int value);

    /**
     *
     * \return
     */
    int GetValue() const;
};

/**
 *
 */
class ExampleEvent2 : public CrossEngine::EventBus::Event<ExampleEvent2> {

};

/**
 *
 */
class HelloWorld : public CrossEngine::Application::Application,
                   public CrossEngine::EventBus::EventHandler<
                           ExampleEvent, ExampleEvent2,
                           CrossEngine::Window::Events::MousePosEvent,
                           CrossEngine::Window::Events::KeyEvent
                   > {
private:
    CrossEngine::Window::SharedWindow window; /** */

    CrossEngine::Util::Math::Matrix4 view;
    CrossEngine::Util::Math::Matrix4 projection;
    CrossEngine::Util::Math::Vector2 angle;
    CrossEngine::Util::Math::Vector2 old;
    CrossEngine::Util::Math::Vector3 up;

    CrossEngine::Util::Math::Vector3 cameraPosition;
    CrossEngine::Util::Math::Vector3 cameraFront;
    CrossEngine::Util::Math::Vector3 cameraUp;

    bool firstMove = true;

public:
    /**
     *
     */
    void OnStartup() override;

    /**
     *
     */
    void OnShutdown() override;

    /**
     *
     * \param event
     */
    void HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent> &event) override;

    /**
     *
     * \param event
     */
    void HandleEvent(const CrossEngine::Util::Memory::Shared<ExampleEvent2> &event) override;

    /**
     *
     * \param event
     */
    void HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::MousePosEvent> &event) override;

    /**
     *
     * \param event
     */
    void HandleEvent(const CrossEngine::Util::Memory::Shared<CrossEngine::Window::Events::KeyEvent> &event) override;

};

CE_DEFINE_APPLICATION(HelloWorld);


#endif //CROSSENGINE_HELLOWORLD_HPP
