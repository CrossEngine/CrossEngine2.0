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
            /**
             *
             */
            class BaseEvent {
            private:
                Window *window; /** */

            public:
                /**
                 *
                 * \param window
                 */
                CrossEngineAPI explicit BaseEvent(Window *window);

                /**
                 *
                 */
                CrossEngineAPI ~BaseEvent();

                /**
                 *
                 * \return
                 */
                CrossEngineAPI Window *GetWindow() const;
            };

            /**
             *
             */
            class KeyEvent : public BaseEvent, public EventBus::Event<KeyEvent> {
            private:
                int key; /** */
                int scan; /** */
                int action; /** */
                int mods; /** */

            public:
                /**
                 *
                 * \param window
                 * \param key
                 * \param scan
                 * \param action
                 * \param mods
                 */
                CrossEngineAPI KeyEvent(Window *window, int key, int scan, int action, int mods);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetKey() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetScan() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetAction() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetMods() const;
            };

            /**
             *
             */
            class CharEvent : public BaseEvent, public EventBus::Event<CharEvent> {
            private:
                unsigned int code; /** */
                int mods; /** */

            public:
                /**
                 *
                 * \param window
                 * \param code
                 * \param mods
                 */
                CrossEngineAPI CharEvent(Window *window, unsigned int code, int mods);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI unsigned int GetCode() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetMods() const;
            };

            /**
             *
             */
            class MouseButtonEvent : public BaseEvent, public EventBus::Event<MouseButtonEvent> {
            private:
                int button; /** */
                int action; /** */
                int mods; /** */

            public:
                /**
                 *
                 * \param window
                 * \param button
                 * \param action
                 * \param mods
                 */
                CrossEngineAPI MouseButtonEvent(Window *window, int button, int action, int mods);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetButton() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetAction() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetMods() const;

            };

            /**
             *
             */
            class MousePosEvent : public BaseEvent, public EventBus::Event<MousePosEvent> {
            private:
                double dx; /** */
                double dy; /** */
            public:
                /**
                 *
                 * \param window
                 * \param dx
                 * \param dy
                 */
                CrossEngineAPI MousePosEvent(Window *window, double dx, double dy);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI double GetX() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI double GetY() const;
            };

            /**
             *
             */
            class MouseEnterEvent : public BaseEvent, public EventBus::Event<MouseEnterEvent> {
            private:
                bool entered; /** */

            public:
                /**
                 *
                 * \param window
                 * \param entered
                 */
                CrossEngineAPI MouseEnterEvent(Window *window, bool entered);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI bool GetEntered() const;
            };

            /**
             *
             */
            class MouseScrollEvent : public BaseEvent, public EventBus::Event<MouseScrollEvent> {
            private:
                double dx; /** */
                double dy; /** */
            public:
                /**
                 *
                 * \param window
                 * \param dx
                 * \param dy
                 */
                CrossEngineAPI MouseScrollEvent(Window *window, double dx, double dy);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI double GetX() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI double GetY() const;
            };

            /**
             *
             */
            class DropEvent : public BaseEvent, public EventBus::Event<DropEvent> {
            private:
                Util::StringVector paths; /** */

            public:
                /**
                 *
                 * \param window
                 * \param count
                 * \param paths
                 */
                CrossEngineAPI DropEvent(Window *window, int count, const char **paths);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI Util::StringVector GetPaths() const;
            };

            /**
             *
             */
            class WindowPosEvent : public BaseEvent, public EventBus::Event<WindowPosEvent> {
            private:
                int x; /** */
                int y; /** */

            public:
                /**
                 *
                 * \param window
                 * \param x
                 * \param y
                 */
                CrossEngineAPI WindowPosEvent(Window *window, int x, int y);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetX() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetY() const;

            };

            /**
             *
             */
            class WindowSizeEvent : public BaseEvent, public EventBus::Event<WindowSizeEvent> {
            private:
                int width; /** */
                int height; /** */

            public:
                /**
                 *
                 * \param window
                 * \param width
                 * \param height
                 */
                CrossEngineAPI WindowSizeEvent(Window *window, int width, int height);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetWidth() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetHeight() const;

            };

            /**
             *
             */
            class WindowCloseEvent : public BaseEvent, public EventBus::Event<WindowCloseEvent> {
            private:

            public:
                /**
                 *
                 * \param window
                 */
                CrossEngineAPI explicit WindowCloseEvent(Window *window);

            };

            /**
             *
             */
            class WindowRefreshEvent : public BaseEvent, public EventBus::Event<WindowRefreshEvent> {
            private:

            public:
                /**
                 *
                 * \param window
                 */
                CrossEngineAPI explicit WindowRefreshEvent(Window *window);

            };

            /**
             *
             */
            class WindowFocusEvent : public BaseEvent, public EventBus::Event<WindowFocusEvent> {
            private:
                bool focused; /** */

            public:
                /**
                 *
                 * \param window
                 * \param focused
                 */
                CrossEngineAPI WindowFocusEvent(Window *window, bool focused);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI bool GetFocused() const;

            };

            /**
             *
             */
            class WindowIconifyEvent : public BaseEvent, public EventBus::Event<WindowIconifyEvent> {
            private:
                bool iconified; /** */

            public:
                /**
                 *
                 * \param window
                 * \param iconified
                 */
                CrossEngineAPI WindowIconifyEvent(Window *window, bool iconified);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI bool GetIconified() const;

            };

            /**
             *
             */
            class FramebufferSizeEvent : public BaseEvent, public EventBus::Event<FramebufferSizeEvent> {
            private:
                int width; /** */
                int height; /** */

            public:
                /**
                 *
                 * \param window
                 * \param width
                 * \param height
                 */
                CrossEngineAPI FramebufferSizeEvent(Window *window, int width, int height);

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetWidth() const;

                /**
                 *
                 * \return
                 */
                CrossEngineAPI int GetHeight() const;

            };

        }
    }
}


#endif //CROSSENGINE_BUILDNUMBER_WINDOWEVENTS_HPP
