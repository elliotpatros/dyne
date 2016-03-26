//
//  Time.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Time__
#define __dyne__Time__

#include "DyneBase.h"
#include "OpenGLBase.h"

class Time
{
public:
    static Time& getInstance(void) noexcept;
    
    // gets
    GLfloat getCurrent(void) const noexcept;
    GLfloat getDelta(void) const noexcept;
    GLfloat getDeltaSq(void) const noexcept;
    GLfloat getHalfDeltaSq(void) const noexcept;
    static GLfloat getTimeStretch(void) noexcept;
    GLfloat getStretchedDelta(void) const noexcept;
    GLfloat getStretchedDeltaSq(void) const noexcept;
    GLfloat getStretchedHalfDeltaSq(void) const noexcept;
    
    // sets
    void update(void) noexcept;
    void pause(void) noexcept;
    void play(void) noexcept;
    static void setTimeStretch(const GLfloat t) noexcept;
    static bool stretchIsThreadSafe;
    
private:
    // singleton stuff
    Time(void) :
    paused {false},
    last {1.f}
    {}
    Time(Time const&);
    void operator= (Time const&);
    
    // properties
    bool paused;
    GLfloat current;
    static GLfloat delta;
    GLfloat deltaSq;
    GLfloat halfDeltaSq;
    GLfloat last;
    
    static GLfloat timeStretch;
    static GLfloat stretchedDelta;
    GLfloat stretchedDeltaSq;
    GLfloat stretchedHalfDeltaSq;
};

#endif
