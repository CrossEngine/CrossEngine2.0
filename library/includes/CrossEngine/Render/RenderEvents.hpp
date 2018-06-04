/**************************************************************
 * Program Title: CrossEngine
 * Filename: RenderEvents.hpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_RENDEREVENTS_HPP
#define CROSSENGINE_RENDEREVENTS_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Util.hpp>
#include <CrossEngine/EventBus/Event.hpp>

#include <GLFW/glfw3.h>

namespace CrossEngine {
    namespace Render {
        class Renderer;
        namespace Events {
            class BaseEvent {

            };

            class PlayPauseEvent: public BaseEvent, public EventBus::Event<PlayPauseEvent> {
            private:
                bool paused;

            public:
                CrossEngineAPI explicit PlayPauseEvent(bool paused);

                CrossEngineAPI ~PlayPauseEvent();

                bool GetPaused() const;
            };

            typedef Util::Memory::Shared<PlayPauseEvent> SharedPlayPauseEvent;

        }
    }
}


#endif //CROSSENGINE_RENDEREVENTS_HPP
