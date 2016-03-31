//
//  Physics.h
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Physics__
#define __dyne__Physics__

#include "DyneBase.h"
#include "GLMBase.h"
#include "Maths.h"

#include "Timer.h" // for setting physics clock
#include "Time.h"  // for getting altered time (e.g. stretched, paused)

class Physics : public Timer
{
public:
    Physics(void);
    ~Physics(void);
    
//    void setup(const float clockHz);
    void timerCallback(void);
    
    int instance;
    static unsigned loopNum;
    static pthread_mutex_t lock;
    
    
private:
    
};


#endif
