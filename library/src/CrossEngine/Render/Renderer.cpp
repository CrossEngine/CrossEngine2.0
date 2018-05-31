/**************************************************************
 * Program Title: CrossEngine
 * Filename: Renderer.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/Renderer.hpp>


CrossEngine::Render::Renderer::Renderer() {
    log = CrossEngine::Logging::GetLogger("Renderer");
}

CrossEngine::Render::Renderer::~Renderer() {
    log = nullptr;
}

bool CrossEngine::Render::Renderer::Setup(GLFWwindow *window) {
    return false;
}

bool CrossEngine::Render::Renderer::Render(GLFWwindow *window) {
    return false;
}

bool CrossEngine::Render::Renderer::Teardown(GLFWwindow *window) {
    return false;
}
