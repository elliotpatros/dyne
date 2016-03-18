/*
 *  Application.h
 *  dyne
 *  
 *  wrapper for GLFW window
 *
 *  Created by Elliot Patros on 3/18/16.
 *  Copyright (c) 2016 Elliot Patros. All rights reserved.
 */

#ifndef __dyne__Application__
#define __dyne__Application__

#include "DyneBase.h"
#include "Timer.h"

class Application : private Timer
{
public:
    static Application& getInstance(void);
    
    void setup(void);
    void run(void) noexcept;
    
    void timerCallback(void) noexcept;
    
    
private:
    // singleton stuff
    Application(void);
    ~Application(void);
    Application(Application const&);
    void operator=(Application const&);
};

#endif
