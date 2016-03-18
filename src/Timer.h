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

class Timer : public PosixThread
{
public:
    Timer(void);
    ~Timer(void);
    
    bool start(void);
    bool startMs(float ms);
    bool startHz(float hz);
    void stop(void);
    
    
private:
    Timer(Timer const&);
    void operator=(Timer const&);
    
    inline void setIntervalMs(float ms) noexcept;
    int intervalMs;
    void threadedFunction(void* posix);
};

#endif
