//
//  OpenGLWindow.cpp
//  dyne
//
//  Created by Elliot Patros on 3/21/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "OpenGLWindow.h"

//==============================================================================
// constructor & destructor
//==============================================================================
OpenGLWindow::OpenGLWindow(void) :
window(nullptr),
glfwIsRunning(false)
{
    
}

OpenGLWindow::~OpenGLWindow(void)
{
    if(glfwIsRunning) {glfwTerminate(); }
}

//==============================================================================
// start up
//==============================================================================
bool OpenGLWindow::setup(const string title, const ivec2 size) noexcept
{
    if (setupGLFW()) {return true; }
    if (makeWindow(title, size)) {return true; }
    if (setupGLEW()) {return true; }
    
    return false;
}

bool OpenGLWindow::setupGLFW(void) noexcept
{   // returns true if errors
    if ((glfwIsRunning = glfwInit()) == GL_FALSE)
    {
        IO::post("failed to start GLFW");
        return true;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    
    return false;
}

bool OpenGLWindow::setupGLEW(void) noexcept
{   // returns true if errors
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        IO::post("failed to start GLEW");
        return true;
    }
    
    glViewport(0, 0, windowSize.x, windowSize.y);
    
    // set OpenGL properties
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_MULTISAMPLE);
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace (GL_CCW);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glfwSwapInterval (1);
    
    
    return false;
}

bool OpenGLWindow::makeWindow(const string title, const ivec2 size) noexcept
{   // returns true if errors
    // make window
    window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
    if (window == nullptr)
    {
        IO::post("failed to create GLFW window");
        return true;
    }
    
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
    
    return false;
}

//==============================================================================
// visibility
//==============================================================================
void OpenGLWindow::show(void) noexcept {glfwShowWindow(window); }
void OpenGLWindow::hide(void) noexcept {glfwHideWindow(window); }

//==============================================================================
// loop
//==============================================================================
void OpenGLWindow::loop(void) noexcept
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
