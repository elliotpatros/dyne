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

#include "OpenGLWindow.h"

class Application
{
public:
    static Application& getInstance(void);
    
    bool setup(void);
    void run(void) noexcept;
    
    
private:
    // singleton stuff
    Application(void);
    ~Application(void);
    Application(Application const&);
    void operator=(Application const&);
    
    OpenGLWindow* mainWindow;
};

#endif
