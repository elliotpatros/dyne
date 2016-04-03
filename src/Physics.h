//
//  Physics.h
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Physics__
#define __dyne__Physics__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"
#include "Maths.h"

#include "Timer.h" // for setting physics clock
#include "Time.h"  // for getting altered time (e.g. stretched, paused)

struct MassyObject
{
    // constructor
    MassyObject(void) :
    displacement {vec3(0.f)},
    position {vec3(0.f)},
    velocity {vec3(0.f)},
    mass {500000.f},
    radius {getRandomBetween(2.f, 3.f)}
    { }
    
    // state variables
    bool    hit;
    GLfloat mass;
    GLfloat radius;
    vec3    displacement;
    vec3    position;
    vec3    velocity;
};

class Physics : public Timer
{
public:
    // constructor and destructor
    Physics(void);
    ~Physics(void);
    
    // public functions
    void setup(const size_t nMassesAtStart);
    void setNMasses(const size_t n);
    
    // user functions
    static void scaleTime(const GLfloat scale) noexcept;
    static void scaleGravity(const GLfloat scale) noexcept;
    static void scaleCenterMass(const GLfloat scale) noexcept;
    static void pause(const GLfloat pauseIfNonZero) noexcept;
    
    // public variables
    static pthread_mutex_t lock;
    vector<MassyObject> masses;
    
    
private:
    // calculates one frame of all physical interactions
    void timerCallback(void) noexcept;    
    static bool readyToPlay;
    
    // physics helper functions
    void accumulateDisplacement(void) noexcept;
    void collide(void) noexcept;
    void moveMasses() noexcept;
    
    // physical objects
    size_t nMasses, nMassesMinusOne;
    static const GLfloat centerMassConstant;
    static GLfloat centerMass;
    
    // threaded variables
    static const GLfloat clockHz, tDeltaConstant;
    static GLfloat tDelta, tHalfDeltaSq, rTDelta;
    
    // gravity
    static const GLfloat elasticity;
    static const GLfloat gravityConstant;
    static GLfloat gravity;
    static Time& time;
};


#endif
