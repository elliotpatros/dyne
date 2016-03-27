//
//  Shader.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Shader__
#define __dyne__Shader__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include <fstream> // for ifstream
#include <sstream> // for stringstream

#define DYNE_MAX_INSTANCES 100

using std::ifstream;
using std::stringstream;
using std::istreambuf_iterator;

class Shader
{
public:
    Shader(void);
    explicit Shader(const string vsDir, const string fsDir);
    
    bool checkCompileError(const GLuint shader) const noexcept;
    bool checkLinkingError(const GLuint program) const noexcept;
    
    void use(void) const noexcept;
    GLuint getId(void) const noexcept;
    GLuint useAndGetId(void) const noexcept;
    
    
private:
    GLuint programId;
    static const string glslPath;
};

#endif
