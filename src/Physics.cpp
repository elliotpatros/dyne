//
//  Physics.cpp
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Physics.h"

float Physics::clockHz {200.f};

Physics::Physics(void) {}

Physics::~Physics(void) {}

void Physics::timerCallback(void)
{
    // do work here
    pthread_mutex_lock(&lock);
    // write variables here
    pthread_mutex_unlock(&lock);
}

//void Physics::setup(const float clockHz)
//{
//    pthread_mutex_init(&Physics::lock, NULL);
//    startHz(hz);
//}