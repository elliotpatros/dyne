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
    return runPThread();
}

bool Timer::startMs(float ms)
{
    setIntervalMs(ms);
    return runPThread();
}

bool Timer::startHz(float hz)
{
    setIntervalMs(hzToMs(hz));
    return runPThread();
}

void Timer::stop(void)
{
    joinPThread();
}

void Timer::threadedFunction(void* posix)
{
    PosixThread* const t = (PosixThread *)posix;
    
    for (int i = 0; i < 40; ++i)
    {
        usleep(intervalMs);
        cout << i << "...\n";
        if (shouldQuit(t)) {return; }
    }
}

void Timer::setIntervalMs(float ms) noexcept
{
    intervalMs = roundToInt(ms * 1000.f);
}