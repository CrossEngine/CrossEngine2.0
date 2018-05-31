/**************************************************************
 * Program Title: CrossEngine_BuildNumber
 * Filename: Window.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Window/Window.hpp>

#include <iostream>

struct UserPointerType {
    CrossEngine::EventBus::EventBus::SharedEventBus eb;
    CrossEngine::Window::Window* window;
};

static void KeyCallback(GLFWwindow *window, int key, int scan, int action, int mods) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::KeyEvent>(
            data->window, key, scan, action, mods
    );
}

static void CharCallback(GLFWwindow *window, unsigned int code) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::CharEvent>(
            data->window, code, 0
    );
}

static void CharModsCallback(GLFWwindow *window, unsigned int code, int mods) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::CharEvent>(
            data->window, code, mods
    );
}

static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::MouseButtonEvent>(
            data->window, button, action, mods
    );
}

static void CursorPosCallback(GLFWwindow *window, double dx, double dy) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::MousePosEvent>(
            data->window, dx, dy
    );
}

static void CursorEnterCallback(GLFWwindow *window, int entered) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::MouseEnterEvent>(
            data->window, entered
    );
}

static void ScrollCallback(GLFWwindow *window, double dx, double dy) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::MouseScrollEvent>(
            data->window, dx, dy
    );
}

static void DropCallback(GLFWwindow *window, int count, const char **paths) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::DropEvent>(
            data->window, count, paths
    );
}

static void WindowPosCallback(GLFWwindow *window, int x, int y) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowPosEvent>(
            data->window, x, y
    );
}

static void WindowSizeCallback(GLFWwindow *window, int width, int height) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowSizeEvent>(
            data->window, width, height
    );
}

static void WindowCloseCallback(GLFWwindow *window) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowCloseEvent>(
            data->window
    );
}

static void WindowRefreshCallback(GLFWwindow *window) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowRefreshEvent>(
            data->window
    );
}

static void WindowFocusCallback(GLFWwindow *window, int focused) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowFocusEvent>(
            data->window, focused==GLFW_TRUE
    );
}

static void WindowIconifyCallback(GLFWwindow *window, int iconified) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::WindowIconifyEvent>(
            data->window, iconified==GLFW_TRUE
    );
}

static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto data = static_cast<UserPointerType *>(glfwGetWindowUserPointer(window));
    data->eb->Publish<CrossEngine::Window::Events::FramebufferSizeEvent>(
            data->window, width, height
    );
}


CrossEngine::Window::Window::Window(
        const CrossEngine::Util::String& name,
        int width, int height,
        CrossEngine::Window::RenderAPI api,
        const CrossEngine::EventBus::EventBus::SharedEventBus& eventBus,
        const CrossEngine::Render::SharedRenderer& renderer) {
    switch (api) {
        case API_OpenGL:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
            break;
        case API_OpenGLES:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            break;
        case API_Vulkan:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            break;
    }
    windowBus = eventBus;
    this->renderer = renderer;
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    resourceContext = glfwCreateWindow(1, 1, "Resources", nullptr, nullptr);
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, resourceContext);
    if (IsValid()) {
        glfwShowWindow(window);

        glfwSetWindowUserPointer(window, new UserPointerType{windowBus, this});

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetCharCallback(window, CharCallback);
        glfwSetCharModsCallback(window, CharModsCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, CursorPosCallback);
        glfwSetCursorEnterCallback(window, CursorEnterCallback);
        glfwSetScrollCallback(window, ScrollCallback);
        glfwSetDropCallback(window, DropCallback);
        glfwSetWindowPosCallback(window, WindowPosCallback);
        glfwSetWindowSizeCallback(window, WindowSizeCallback);
        glfwSetWindowCloseCallback(window, WindowCloseCallback);
        glfwSetWindowRefreshCallback(window, WindowRefreshCallback);
        glfwSetWindowFocusCallback(window, WindowFocusCallback);
        glfwSetWindowIconifyCallback(window, WindowIconifyCallback);
        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    }
}

CrossEngine::Window::Window::~Window() {
    glfwDestroyWindow(window);
    glfwDestroyWindow(resourceContext);
    window = nullptr;
}

bool CrossEngine::Window::Window::IsValid() {
    return window != nullptr;
}

bool CrossEngine::Window::Window::ShouldClose() {
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void CrossEngine::Window::Window::Pulse() {
    windowBus->Pulse();
}

void CrossEngine::Window::Window::StartRenderLoop() {
    if (!renderThread.joinable()) {
        glfwMakeContextCurrent(nullptr); // make sure that there is no current context on this thread
        renderThread = std::thread(&CrossEngine::Window::Window::PrivateRenderLoop, this);
    }
}

void CrossEngine::Window::Window::StopRenderLoop() {
    isRendering = false;
    if (renderThread.joinable()) {
        renderThread.join();
    }
}

void CrossEngine::Window::Window::PrivateRenderLoop() {
    isRendering = true;
    if (renderer->Setup(window)) {
        while (isRendering) {
            renderer->Render(window);
        }
        renderer->Teardown(window);
    }
}
