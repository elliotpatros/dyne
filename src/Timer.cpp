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

Timer::~Timer(void)
{
    stop();
}

bool Timer::start(void)
{
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
    
    while (!shouldQuit(t))
    {
        t->timerCallback();
        
        if (shouldQuit(t)) {return; }
        usleep(intervalMs);
    }
}

void Timer::setIntervalMs(float ms) noexcept
{
    intervalMs = roundToInt(ms * 1000.f);
}
