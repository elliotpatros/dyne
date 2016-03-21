//
//  Application.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Application.h"

Application& Application::getInstance(void)
{
    static Application instance;
    return instance;
}

Application::Application(void)
{
    
}

Application::~Application(void)
{
    
}

void Application::setup(void)
{
    
}

void Application::run(void) noexcept
{
    startHz(60.f);
    usleep(1000*100);
}

void Application::timerCallback(void) noexcept
{
    cout << "fuc yesh!\n";
}