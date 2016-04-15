//
//  Timer.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Timer.h"

Timer::Timer(void)
{
    setIntervalMs(1000.f);
    stop();
}

void Timer::setHz(float hz)
{
    setIntervalMs(hzToMs(hz));
}

bool Timer::start(void)
{
    totime = system_clock::now() + intervalMicro;
    
    return runThread();
}

bool Timer::startMs(float ms)
{
    setIntervalMs(ms);
    return start();
}

bool Timer::startHz(float hz)
{
    setIntervalMs(hzToMs(hz));
    return start();
}

void Timer::stop(void)
{
    cancelThread();
}

void Timer::threadedFunction(void* arg) noexcept
{
    Timer* const t = (Timer *)arg;
    
    while (!t->shouldQuit)
    {
        t->timerCallback();
        const system_clock::time_point now (system_clock::now());
        totime += intervalMicro;
        if (totime > now) {sleep_until(totime); }
        else              {totime = now + intervalMicro; }
    }
}

void Timer::setIntervalMs(float ms) noexcept
{
    intervalMicro = (microseconds)llroundl(ms * 1000.f);
}
