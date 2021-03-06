//
//  CubeMap.h
//  dyne
//
//  Created by Elliot Patros on 3/28/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__CubeMap__
#define __dyne__CubeMap__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"

#include "Model.h"
#include "Shader.h"
#include "Camera.h"

#include "lodepng.h"

class CubeMap
{
public:
    
    void setup(void) noexcept;
    void render(void) noexcept;
    
    static GLuint textureID;
    static const string faceNames[6];
    
private:
    // glsl uniform locations
    static GLuint viewLoc;
    
    // shader, model, and camera
    static Shader shader;
    static Model model;
    static Camera& camera;
};

#endif
