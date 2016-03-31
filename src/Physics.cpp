//
//  Physics.cpp
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Physics.h"

unsigned Physics::loopNum {0};
pthread_mutex_t Physics::lock {0};


Physics::Physics(void) {}

Physics::~Physics(void) {}

void Physics::timerCallback(void)
{
    for (int i = 0; i < INT_MAX/10; ++i);
    pthread_mutex_lock(&lock);
    IO::post("loop ", instance, " = ", loopNum++);
    pthread_mutex_unlock(&lock);
}

//void Physics::setup(const float clockHz)
//{
//    pthread_mutex_init(&Physics::lock, NULL);
//    startHz(hz);
//}