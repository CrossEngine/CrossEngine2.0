/**************************************************************
 * Program Title: CrossEngine
 * Filename: RenderEvents.cpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Render/RenderEvents.hpp>

CrossEngine::Render::Events::PlayPauseEvent::PlayPauseEvent(bool paused) {
    this->paused = paused;
}

CrossEngine::Render::Events::PlayPauseEvent::~PlayPauseEvent() {

}

bool CrossEngine::Render::Events::PlayPauseEvent::GetPaused() const {
    return paused;
}
