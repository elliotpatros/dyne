//
//  GravityBall.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__GravityBall__
#define __dyne__GravityBall__

#include "DyneBase.h"

#include "Model.h"
#include "Shader.h"
#include "Camera.h"

class GravityBall
{
public:
    GravityBall(void);
    
    static void render(void) noexcept;
    static void setup(void) noexcept;
    
    
private:
    // glsl uniform locations
    static GLuint viewPosLoc;
    static GLuint projectionLoc;
    static GLuint modelLoc[DYNE_MAX_INSTANCES];
    
    // shader, model, and camera
    static Shader shader;
    static Model sphere;
    static Camera& camera;
    
    // all balls
    static vector<GravityBall*> gravityBalls;
};

#endif
