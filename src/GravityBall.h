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
    static GLuint modelLoc[100];
    
    // gravity ball transform matrix
//    void updateGraphics(void) noexcept;
    
    // camera
    static Camera& camera;
//    static void updateCamera(void) noexcept;
    
    // shader and model
    static Shader shader;
    static Model sphere;
    
    // all balls
    static vector<GravityBall*> gravityBalls;
};

#endif
