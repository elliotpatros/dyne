//
//  MassyObject.h
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__MassyObject__
#define __dyne__MassyObject__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"
#include "Maths.h"

class MassyObject
{
public:
    MassyObject(void);
    ~MassyObject(void);
    
    
private:
    vec3    displacement;
    vec3    position;
    vec3    velocity;
    GLfloat mass;
    GLfloat radius;
};

#endif
