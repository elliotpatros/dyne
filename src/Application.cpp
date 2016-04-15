//
//  Application.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Application.h"

//==============================================================================
// constructor & destructor
//==============================================================================
Application& Application::getInstance(void)
{
    static Application instance;
    return instance;
}


Application::Application(void) :
mainWindow(nullptr)
{
    mainWindow = new OpenGLWindow();
}

Application::~Application(void)
{
    if (mainWindow != nullptr) {delete mainWindow; }
    mainWindow = nullptr;
}

//==============================================================================
// start up
//==============================================================================
bool Application::setup(void)
{   // returns true if errors
    if (mainWindow->setup("dyne", {0, 0})) {return true; }
    
    return false;
}

//==============================================================================
// loop
//==============================================================================
void Application::run(void) noexcept
{
    mainWindow->show();
    mainWindow->loop();
}
