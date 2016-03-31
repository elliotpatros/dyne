//
//  Physics.cpp
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Physics.h"

//==============================================================================
// static variables
//==============================================================================
// gravity
float Physics::clockHz {200.f};
const GLfloat Physics::gravityConstant {6.67408f * powf (10.f, -11.f) };
GLfloat Physics::gravityScaler {1000000.f};
GLfloat Physics::gravity {gravityConstant * gravityScaler};
Time& Physics::time {Time::getInstance() };

//==============================================================================
// constructor and destructor
//==============================================================================
Physics::Physics(void) {}
Physics::~Physics(void) {}

//==============================================================================
// public functions
//==============================================================================
//void Physics::setup(const float clockHz)
//{
//    pthread_mutex_init(&Physics::lock, NULL);
//    startHz(hz);
//}

//==============================================================================
// threaded physics update
//==============================================================================
void Physics::timerCallback(void)
{
    // do work here
    pthread_mutex_lock(&lock);
    // write variables here
    pthread_mutex_unlock(&lock);
}

//==============================================================================
// physics helper functions
//==============================================================================





