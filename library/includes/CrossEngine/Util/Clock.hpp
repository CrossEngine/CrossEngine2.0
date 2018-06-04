/**************************************************************
 * Program Title: CrossEngine
 * Filename: Clock.hpp
 * Author: Blake Rogan
 * Last modified: 1/06/2018
 * Description: 
 * Copyright: CrossEngine (c) 2018
 ***************************************************************/
#ifndef CROSSENGINE_CLOCK_HPP
#define CROSSENGINE_CLOCK_HPP

#include <CrossEngine/config.h>
#include <CrossEngine/Util/Memory.hpp>

#include <chrono>

namespace CrossEngine {
    namespace Util {
        namespace Clock {

            typedef float DeltaTime;

            class Clock {
            private:
                typedef std::chrono::duration<DeltaTime> DeltaDuration;
                typedef std::chrono::high_resolution_clock ChronoClock;
                typedef ChronoClock::time_point TimePoint;
                typedef ChronoClock::duration Duration;

                TimePoint start;

            public:
                CrossEngineAPI Clock();

                CrossEngineAPI ~Clock();

                CrossEngineAPI virtual DeltaTime Tick();

            };

            typedef Util::Memory::Shared<Clock> SharedClock;

            CrossEngineAPI SharedClock GetClock();

            CrossEngineAPI void SetClock(const SharedClock& clock);

            CrossEngineAPI DeltaTime Tick();

        }
    }
}


#endif //CROSSENGINE_CLOCK_HPP
