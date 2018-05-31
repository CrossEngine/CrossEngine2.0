/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: WindowManager.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Window/WindowManager.hpp>

CrossEngine::Window::WindowManager::WindowManager(const CrossEngine::EventBus::EventBus::SharedEventBus &eventBus) {
    managerEventBus = eventBus;
    log = CrossEngine::Logging::GetLogger("WindowManager");
    log->info("Created window manager");
}

CrossEngine::Window::WindowManager::~WindowManager() {
    log->info("Destroyed window manager");
}

bool CrossEngine::Window::WindowManager::Pulse() {
    glfwPollEvents();
    managerEventBus->Pulse();
    windows.erase(std::remove_if(windows.begin(), windows.end(), [](const CrossEngine::Window::SharedWindow& window) {
        window->Pulse();
        if (window->ShouldClose()) {
            window->StopRenderLoop();
            return true;
        }
        return false;
    }), windows.end());
    return windows.empty();
}

