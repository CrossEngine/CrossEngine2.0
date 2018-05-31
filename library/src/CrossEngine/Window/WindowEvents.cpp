/**************************************************************
 * Program Title: CrossEngine
 * Filename: WindowEvents.cpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Window/WindowEvents.hpp>

CrossEngine::Window::Events::BaseEvent::BaseEvent(CrossEngine::Window::Window *window) {
    this->window = window;
}

CrossEngine::Window::Events::BaseEvent::~BaseEvent() {
    window = nullptr;
}

CrossEngine::Window::Window *CrossEngine::Window::Events::BaseEvent::GetWindow() const {
    return window;
}

CrossEngine::Window::Events::KeyEvent::KeyEvent(CrossEngine::Window::Window *window, int key, int scan, int action,
                                                int mods) : CrossEngine::Window::Events::BaseEvent(window) {
    this->key = key;
    this->scan = scan;
    this->action = action;
    this->mods = mods;
}

int CrossEngine::Window::Events::KeyEvent::GetKey() const {
    return key;
}

int CrossEngine::Window::Events::KeyEvent::GetScan() const {
    return scan;
}

int CrossEngine::Window::Events::KeyEvent::GetAction() const {
    return action;
}

int CrossEngine::Window::Events::KeyEvent::GetMods() const {
    return mods;
}

CrossEngine::Window::Events::CharEvent::CharEvent(CrossEngine::Window::Window *window, unsigned int code, int mods)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->code = code;
    this->mods = mods;
}

unsigned int CrossEngine::Window::Events::CharEvent::GetCode() const {
    return code;
}

int CrossEngine::Window::Events::CharEvent::GetMods() const {
    return mods;
}

CrossEngine::Window::Events::MouseButtonEvent::MouseButtonEvent(CrossEngine::Window::Window *window, int button,
                                                                int action, int mods)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->button = button;
    this->action = action;
    this->mods = mods;
}

int CrossEngine::Window::Events::MouseButtonEvent::GetButton() const {
    return button;
}

int CrossEngine::Window::Events::MouseButtonEvent::GetAction() const {
    return action;
}

int CrossEngine::Window::Events::MouseButtonEvent::GetMods() const {
    return mods;
}

CrossEngine::Window::Events::MousePosEvent::MousePosEvent(CrossEngine::Window::Window *window, double dx, double dy)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->dx = dx;
    this->dy = dy;
}

double CrossEngine::Window::Events::MousePosEvent::GetX() const {
    return dx;
}

double CrossEngine::Window::Events::MousePosEvent::GetY() const {
    return dy;
}

CrossEngine::Window::Events::MouseEnterEvent::MouseEnterEvent(CrossEngine::Window::Window *window, bool entered)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->entered = entered;
}

bool CrossEngine::Window::Events::MouseEnterEvent::GetEntered() const {
    return entered;
}

CrossEngine::Window::Events::MouseScrollEvent::MouseScrollEvent(CrossEngine::Window::Window *window, double dx,
                                                                double dy) : CrossEngine::Window::Events::BaseEvent(
        window) {
    this->dx = dx;
    this->dy = dy;
}

double CrossEngine::Window::Events::MouseScrollEvent::GetX() const {
    return dx;
}

double CrossEngine::Window::Events::MouseScrollEvent::GetY() const {
    return dy;
}

CrossEngine::Window::Events::DropEvent::DropEvent(CrossEngine::Window::Window *window, int count, const char **paths)
        : CrossEngine::Window::Events::BaseEvent(window) {
    for (int i = 0; i < count; i++) {
        this->paths.push_back(paths[i]);
    }
}

CrossEngine::Util::StringVector CrossEngine::Window::Events::DropEvent::GetPaths() const {
    return paths;
}

CrossEngine::Window::Events::WindowPosEvent::WindowPosEvent(CrossEngine::Window::Window *window, int x, int y)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->x = x;
    this->y = y;
}

int CrossEngine::Window::Events::WindowPosEvent::GetX() const {
    return x;
}

int CrossEngine::Window::Events::WindowPosEvent::GetY() const {
    return y;
}

CrossEngine::Window::Events::WindowSizeEvent::WindowSizeEvent(CrossEngine::Window::Window *window, int width,
                                                              int height) : CrossEngine::Window::Events::BaseEvent(
        window) {
    this->width = width;
    this->height = height;
}

int CrossEngine::Window::Events::WindowSizeEvent::GetWidth() const {
    return width;
}

int CrossEngine::Window::Events::WindowSizeEvent::GetHeight() const {
    return height;
}

CrossEngine::Window::Events::WindowCloseEvent::WindowCloseEvent(CrossEngine::Window::Window *window)
        : CrossEngine::Window::Events::BaseEvent(window) {

}

CrossEngine::Window::Events::WindowRefreshEvent::WindowRefreshEvent(CrossEngine::Window::Window *window)
        : CrossEngine::Window::Events::BaseEvent(window) {

}

CrossEngine::Window::Events::WindowFocusEvent::WindowFocusEvent(CrossEngine::Window::Window *window, bool focused)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->focused = focused;
}

bool CrossEngine::Window::Events::WindowFocusEvent::GetFocused() const {
    return focused;
}

CrossEngine::Window::Events::WindowIconifyEvent::WindowIconifyEvent(CrossEngine::Window::Window *window,
                                                                    bool iconified)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->iconified = iconified;
}

bool CrossEngine::Window::Events::WindowIconifyEvent::GetIconified() const {
    return iconified;
}

CrossEngine::Window::Events::FramebufferSizeEvent::FramebufferSizeEvent(CrossEngine::Window::Window *window, int width,
                                                                        int height)
        : CrossEngine::Window::Events::BaseEvent(window) {
    this->width = width;
    this->height = height;
}

int CrossEngine::Window::Events::FramebufferSizeEvent::GetWidth() const {
    return width;
}

int CrossEngine::Window::Events::FramebufferSizeEvent::GetHeight() const {
    return height;
}
