//
//  GravityBalls.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__GravityBalls__
#define __dyne__GravityBalls__

#include "DyneBase.h"

#include "Model.h"
#include "Shader.h"
#include "Camera.h"

#include "Cubemap.h"

#include "Physics.h"

class GravityBalls
{
public:
    GravityBalls(void);
    
    void setup(const GLuint nBallsAtStart) noexcept;
    void startPhysics(void) noexcept;
    void render(void) noexcept;
    
    static void setNBalls(const GLfloat n) noexcept;
    
private:
    static GLuint nBalls;
    
    // glsl uniform locations
    static GLuint viewPosLoc;
    static GLuint projectionLoc;
    static GLuint modelLoc[DYNE_MAX_GBALLS];
    static GLuint colorLoc[DYNE_MAX_GBALLS];
    
    // shader, model, and camera
    static Shader shader;
    static Model sphere;
    static Camera& camera;
    
    Physics physics;
};

#endif
