/**************************************************************
 * Program Title: CrossEngine
 * Filename: WindowEvents.hpp
 * Author: Blake Rogan
 * Last modified: 31/05/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_BUILDNUMBER_WINDOWEVENTS_HPP
#define CROSSENGINE_BUILDNUMBER_WINDOWEVENTS_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/EventBus/Event.hpp>

#include <GLFW/glfw3.h>

namespace CrossEngine {
    namespace Window {
        class Window;
        namespace Events {
            class BaseEvent {
            private:
                Window *window;

            public:
                CrossEngineAPI explicit BaseEvent(Window *window);

                CrossEngineAPI ~BaseEvent();

                CrossEngineAPI Window *GetWindow() const;
            };

            class KeyEvent : public BaseEvent, public EventBus::Event<KeyEvent> {
            private:
                int key;
                int scan;
                int action;
                int mods;

            public:
                CrossEngineAPI KeyEvent(Window *window, int key, int scan, int action, int mods);

                CrossEngineAPI int GetKey() const;

                CrossEngineAPI int GetScan() const;

                CrossEngineAPI int GetAction() const;

                CrossEngineAPI int GetMods() const;
            };

            class CharEvent : public BaseEvent, public EventBus::Event<CharEvent> {
            private:
                unsigned int code;
                int mods;

            public:
                CrossEngineAPI CharEvent(Window *window, unsigned int code, int mods);

                CrossEngineAPI unsigned int GetCode() const;

                CrossEngineAPI int GetMods() const;
            };

            class MouseButtonEvent : public BaseEvent, public EventBus::Event<MouseButtonEvent> {
            private:
                int button;
                int action;
                int mods;

            public:
                CrossEngineAPI MouseButtonEvent(Window *window, int button, int action, int mods);

                CrossEngineAPI int GetButton() const;

                CrossEngineAPI int GetAction() const;

                CrossEngineAPI int GetMods() const;

            };

            class MousePosEvent : public BaseEvent, public EventBus::Event<MousePosEvent> {
            private:
                double dx;
                double dy;
            public:
                CrossEngineAPI MousePosEvent(Window *window, double dx, double dy);

                CrossEngineAPI double GetX() const;

                CrossEngineAPI double GetY() const;
            };

            class MouseEnterEvent : public BaseEvent, public EventBus::Event<MouseEnterEvent> {
            private:
                bool entered;

            public:
                CrossEngineAPI MouseEnterEvent(Window *window, bool entered);

                CrossEngineAPI bool GetEntered() const;
            };

            class MouseScrollEvent : public BaseEvent, public EventBus::Event<MouseScrollEvent> {
            private:
                double dx;
                double dy;
            public:
                CrossEngineAPI MouseScrollEvent(Window *window, double dx, double dy);

                CrossEngineAPI double GetX() const;

                CrossEngineAPI double GetY() const;
            };

            class DropEvent : public BaseEvent, public EventBus::Event<DropEvent> {
            private:
                Util::StringVector paths;

            public:
                CrossEngineAPI DropEvent(Window* window, int count, const char** paths);

                CrossEngineAPI Util::StringVector GetPaths() const;
            };

            class WindowPosEvent : public BaseEvent, public EventBus::Event<WindowPosEvent> {
            private:
                int x;
                int y;

            public:
                CrossEngineAPI WindowPosEvent(Window* window, int x, int y);

                CrossEngineAPI int GetX() const;

                CrossEngineAPI int GetY() const;

            };

            class WindowSizeEvent : public BaseEvent, public EventBus::Event<WindowSizeEvent> {
            private:
                int width;
                int height;

            public:
                CrossEngineAPI WindowSizeEvent(Window* window, int width, int height);

                CrossEngineAPI int GetWidth() const;

                CrossEngineAPI int GetHeight() const;

            };

            class WindowCloseEvent : public BaseEvent, public EventBus::Event<WindowCloseEvent> {
            private:

            public:
                CrossEngineAPI explicit WindowCloseEvent(Window* window);

            };

            class WindowRefreshEvent : public BaseEvent, public EventBus::Event<WindowRefreshEvent> {
            private:

            public:
                CrossEngineAPI explicit WindowRefreshEvent(Window* window);

            };

            class WindowFocusEvent : public BaseEvent, public EventBus::Event<WindowFocusEvent> {
            private:
                bool focused;

            public:
                CrossEngineAPI WindowFocusEvent(Window* window, bool focused);

                CrossEngineAPI bool GetFocused() const;

            };

            class WindowIconifyEvent : public BaseEvent, public EventBus::Event<WindowIconifyEvent> {
            private:
                bool iconified;

            public:
                CrossEngineAPI WindowIconifyEvent(Window* window, bool iconified);

                CrossEngineAPI bool GetIconified() const;

            };

            class FramebufferSizeEvent : public BaseEvent, public EventBus::Event<FramebufferSizeEvent> {
            private:
                int width;
                int height;

            public:
                CrossEngineAPI FramebufferSizeEvent(Window* window, int width, int height);

                CrossEngineAPI int GetWidth() const;

                CrossEngineAPI int GetHeight() const;

            };

        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_WINDOWEVENTS_HPP
