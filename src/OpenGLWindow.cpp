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
window (nullptr),
glfwIsRunning (false),
time {Time::getInstance()},
input {Input::getInstance()},
camera {Camera::getInstance()}
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
    
    camera.setWindowProperties(window, windowSize);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//    glfwSetKeyCallback(window, input.keyPressed);
//    glfwSetScrollCallback(window, Camera::handleMouseScroll);
    
    sky.setup();
    balls.setup(2);
    balls.startPhysics();
    oscIn.startThread();
    oscOut.sendBang("/reset-all");
    
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glfwSwapInterval(1);
    
    
    return false;
}

bool OpenGLWindow::makeWindow(const string title, const ivec2 size) noexcept
{   // returns true if errors
    // make window
    GLFWmonitor* mainMonitor (glfwGetPrimaryMonitor());
    if (mainMonitor == nullptr)
    {
        IO::post("could not find primary monitor");
        return true;
    }
    
    const GLFWvidmode* mode = glfwGetVideoMode(mainMonitor);
    window = glfwCreateWindow((size.x < 1) ? mode->width  : size.x,
                              (size.y < 1) ? mode->height : size.y,
                               title.c_str(),
                              (tmax(size.x, size.y) < 1) ? mainMonitor : NULL,
                               NULL);
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
        
        balls.render();
        sky.render();
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        time.update();
        input.handleFirstPresses();
        camera.update();
        
        pthread_mutex_lock(&Physics::lock);
        oscOut.sendPhysicsInfo(&Physics::masses);
        pthread_mutex_unlock(&Physics::lock);
    }
}
