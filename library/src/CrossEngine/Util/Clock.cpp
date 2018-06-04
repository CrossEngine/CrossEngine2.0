/**************************************************************
 * Program Title: CrossEngine
 * Filename: Clock.cpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#include <CrossEngine/Util/Clock.hpp>


CrossEngine::Util::Clock::Clock::Clock() {
    start = ChronoClock::now();
}

CrossEngine::Util::Clock::Clock::~Clock() {

}

CrossEngine::Util::Clock::DeltaTime CrossEngine::Util::Clock::Clock::Tick() {
    TimePoint now = ChronoClock::now();
    DeltaDuration tick = now - start;
    return tick.count();
}


CrossEngine::Util::Clock::SharedClock systemClock = nullptr;

CrossEngine::Util::Clock::SharedClock CrossEngine::Util::Clock::GetClock() {
    return systemClock;
}

void CrossEngine::Util::Clock::SetClock(const CrossEngine::Util::Clock::SharedClock &clock) {
    systemClock = clock;
}

CrossEngine::Util::Clock::DeltaTime CrossEngine::Util::Clock::Tick() {
    if (systemClock) {
        return systemClock->Tick();
    }
    return 0;
}
