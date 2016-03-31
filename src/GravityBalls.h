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

#include "Time.h"
#include "Cubemap.h"

class GravityBalls
{
public:
    GravityBalls(void);
    
    void setup(const GLuint nBallsAtStart) noexcept;
    void render(void) noexcept;
    
    
private:
    GLuint nBalls;
    
    // glsl uniform locations
    static GLuint viewPosLoc;
    static GLuint projectionLoc;
    static GLuint modelLoc[DYNE_MAX_GBALLS];
    static GLuint colorLoc[DYNE_MAX_GBALLS];
//    static GLuint skyboxLoc;
    
    // shader, model, and camera
    static Shader shader;
    static Model sphere;
    static Camera& camera;
};

#endif
