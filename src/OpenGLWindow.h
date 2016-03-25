//
//  OpenGLWindow.h
//  dyne
//
//  Created by Elliot Patros on 3/21/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__OpenGLWindow__
#define __dyne__OpenGLWindow__

#include "DyneBase.h"
#include "GLMBase.h"
#include "OpenGLBase.h"

class OpenGLWindow
{
public:
    OpenGLWindow(void);
    ~OpenGLWindow(void);
    
    // start up
    bool setup(const string title, const ivec2 size) noexcept;
    
    // visibility
    void show(void) noexcept;
    void hide(void) noexcept;
    
    // game loop
    void loop(void) noexcept;
    
    
private:
    // GLFW
    GLFWwindow* window;
    bool glfwIsRunning;
    bool setupGLFW(void) noexcept;
    bool makeWindow(const string title, const ivec2 size) noexcept;
    
    // GLEW
    bool setupGLEW(void) noexcept;
    
    // size (pixels)
    ivec2 windowSize;
};

#endif
