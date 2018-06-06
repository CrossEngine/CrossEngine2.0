/**************************************************************
 * Program Title: CrossEngine
 * Filename: Renderer.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/Renderer.hpp>
#include <CrossEngine/Window/Window.hpp>


CrossEngine::Render::Renderer::Renderer() {
    log = CrossEngine::Logging::GetLogger("Renderer");
}

CrossEngine::Render::Renderer::~Renderer() {
    log = nullptr;
}

void CrossEngine::Render::Renderer::Create(CrossEngine::Window::Window *window) {
    window->GetWindowBus()->Subscribe<CrossEngine::Render::Events::PlayPauseEvent>(0, this);
}

void CrossEngine::Render::Renderer::Destroy(CrossEngine::Window::Window *window) {
    window->GetWindowBus()->Unsubscribe<CrossEngine::Render::Events::PlayPauseEvent>({0});
}

bool CrossEngine::Render::Renderer::Setup(Window::Window *window) {
    return false;
}

bool CrossEngine::Render::Renderer::Render(Window::Window *window, const Util::DeltaTime& delta) {
    for (const auto& function: renderFunctions) {
        function(window, delta);
    }
    return false;
}

bool CrossEngine::Render::Renderer::Teardown(Window::Window *window) {
    return false;
}

void CrossEngine::Render::Renderer::HandleEvent(const CrossEngine::Render::Events::SharedPlayPauseEvent &event) {
    log->info("Pausing renderer: {}", event->GetPaused());
}

CrossEngine::Render::SharedShaderSource
CrossEngine::Render::Renderer::LoadShaderSource(const CrossEngine::Util::String &name,
                                                const CrossEngine::Util::CharVector &source, GLenum type) {
    return nullptr;
}

CrossEngine::Render::SharedShaderProgram CrossEngine::Render::Renderer::LoadShaderProgram(
        const CrossEngine::Render::ShaderSourceVector &source) {
    return nullptr;
}

void CrossEngine::Render::Renderer::AddRenderFunction(const CrossEngine::Render::RenderFunction &function) {
    renderFunctions.push_back(function);
}

CrossEngine::Render::RenderObject *CrossEngine::Render::Renderer::CreateRenderObject() {
    return new CrossEngine::Render::RenderObject();
}