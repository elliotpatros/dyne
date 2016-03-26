//
//  Time.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Time.h"

#include "Time.h"

GLfloat Time::timeStretch{1.f};
GLfloat Time::delta{1.f};
GLfloat Time::stretchedDelta{0.1f};
bool Time::stretchIsThreadSafe{true};

Time& Time::getInstance(void) noexcept
{
    static Time instance;
    return instance;
}

void Time::update(void) noexcept
{
    // glfwGetTime() returns 0.0 if an error occurs
    if (paused)
    {
        glfwSetTime(current);
    }
    else
    {
        current = (GLfloat)glfwGetTime();
        delta = current - last;
        deltaSq = delta * delta;
        halfDeltaSq = deltaSq * 0.5f;
        last = current;
        
        if (stretchIsThreadSafe)
        {
            stretchedDelta = delta * timeStretch;
            stretchedDeltaSq = stretchedDelta * stretchedDelta;
            stretchedHalfDeltaSq = stretchedDeltaSq * 0.5f;
        }
    }
}

void Time::setTimeStretch(const GLfloat t) noexcept
{
    stretchIsThreadSafe = false;
    timeStretch = t;
    stretchIsThreadSafe = true;
}

// gets
GLfloat Time::getCurrent(void) const noexcept
{
    return current;
}

GLfloat Time::getDelta(void) const noexcept
{
    return delta;
}

GLfloat Time::getDeltaSq(void) const noexcept
{
    return deltaSq;
}

GLfloat Time::getHalfDeltaSq(void) const noexcept
{
    return halfDeltaSq;
}

void Time::pause(void) noexcept
{
    paused = true;
}

void Time::play(void) noexcept
{
    paused = false;
}

GLfloat Time::getTimeStretch(void) noexcept
{
    if (delta == 0.f)
    {
        return 0.f;
    }
    else
    {
        return stretchedDelta / delta;
    }
}

GLfloat Time::getStretchedDelta(void) const noexcept
{
    return stretchedDelta;
}

GLfloat Time::getStretchedDeltaSq(void) const noexcept
{
    return stretchedDeltaSq;
}

GLfloat Time::getStretchedHalfDeltaSq(void) const noexcept
{
    return stretchedHalfDeltaSq;
}
