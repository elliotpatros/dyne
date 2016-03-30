//
//  TimedFunction.h
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__TimedFunction__
#define __dyne__TimedFunction__

#include "DyneBase.h"
#include "PosixThread.h"
#include "Maths.h"
#include <thread> // for sleep_until
#include <ctime>  // for time types (e.g. microseconds)
#include <chrono> // for system_clock

using std::chrono::system_clock;
using std::chrono::microseconds;
using std::this_thread::sleep_until;

class TimedFunction
{
public:
    TimedFunction(void);
    
    bool start(void);
    bool startMs(float ms);
    bool startHz(float hz);
    void stop(void);
    
    virtual void timedFunction(void) = 0;
    
    
private:
    inline void setIntervalMs(float ms) noexcept;
    microseconds intervalMicro;
    system_clock::time_point fromtime, totime;
};

#endif
