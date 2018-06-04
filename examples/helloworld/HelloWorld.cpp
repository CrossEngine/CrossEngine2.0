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
    window = windowManager->NewWindow<CrossEngine::Render::OpenGLRenderer>("Render Window", 800, 450);

    log->info("Building Shaders");

    auto vertex = window->LoadShaderSource("vertex", "void main() {gl_Position = vec4(0, 0, 0, 0);}", GL_VERTEX_SHADER);
    auto fragment = window->LoadShaderSource("fragment", "void main() {}", GL_FRAGMENT_SHADER);

    auto program = window->LoadShaderProgram("main", {vertex, fragment});

    log->info("Shaders have been built");

    window->GetRenderer<CrossEngine::Render::OpenGLRenderer>()->AddRenderFunction([this](CrossEngine::Window::Window* window1, CrossEngine::Util::DeltaTime delta){
        log->info("On Render");
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0, 0, 1);
        glViewport(0, 0, 800, 600);
    });

    window->GetRenderer<CrossEngine::Render::OpenGLRenderer>()->AddRenderFunction([this](CrossEngine::Window::Window* window1, CrossEngine::Util::DeltaTime delta){
        log->info("On Flush: {}", delta);
        glFlush();
    });

    window->SetPaused(false);

//    window->CreateShader();

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
