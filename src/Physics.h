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
    displacement {vec3(0)},
    position {vec3(0)},
    velocity {vec3(0)},
    mass {1},
    radius {1}
    { }
    
    // state variables
    vec3    displacement;
    vec3    position;
    vec3    velocity;
    GLfloat mass;
    GLfloat radius;
};

class Physics : public Timer
{
public:
    // constructor and destructor
    Physics(void);
    ~Physics(void);
    
    // public functions
    void setup(const float clockHz);
    
    
private:
    // calculates one frame of all physical interactions
    void timerCallback(void);
    
    // physical objects
    vector<MassyObject> objects;
    
    // threaded variables
    static float clockHz;
    pthread_mutex_t lock;
    
    // gravity
    static const GLfloat gravityConstant;
    static GLfloat gravityScaler;
    static GLfloat gravity;
    static Time& time;
};


#endif
