//
//  Timer.h
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Timer__
#define __dyne__Timer__

#include "DyneBase.h"
#include "PosixThread.h"
#include "Maths.h"
#include <thread> // for sleep_until
#include <ctime>  // for time types (e.g. microseconds)
#include <chrono> // for system_clock

using std::chrono::system_clock;
using std::chrono::microseconds;
using std::this_thread::sleep_until;

class Timer : private PosixThread
{
public:
    Timer(void);
    
    bool start(void);
    bool startMs(float ms);
    bool startHz(float hz);
    void stop(void);
    void setHz(float hz);
    virtual void timerCallback(void) = 0;
    
    
private:
    Timer(Timer const&);
    void operator=(Timer const&);
    
    inline void setIntervalMs(float ms) noexcept;
    microseconds intervalMicro;
    system_clock::time_point fromtime, totime;
    
    void threadedFunction(void* arg) noexcept;
};

#endif
