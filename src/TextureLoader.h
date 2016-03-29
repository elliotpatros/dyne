//
//  TextureLoader.h
//  dyne
//
//  Created by emp on 3/28/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__TextureLoader__
#define __dyne__TextureLoader__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"
#include "lodepng.h"

class TextureLoader
{
public:
    static void loadPNG(const string directory,
                        GLuint* textureID) noexcept;
};

#endif
