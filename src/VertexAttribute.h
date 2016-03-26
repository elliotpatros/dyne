//
//  VertexAttribute.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__VertexAttribute__
#define __dyne__VertexAttribute__

#include "DyneBase.h"
#include "OpenGLBase.h"

class VertexAttribute
{
public:
    void enable(const GLsizei stride,
                const size_t offset) const noexcept;
protected:
    GLuint location; // glsl shader location
    GLuint nValues; // e.g. position has 3 (x, y, z)
    string name;
};

class VA_Position : private VertexAttribute
{
public:
    VA_Position(void);
};

class VA_Normal : private VertexAttribute
{
public:
    VA_Normal(void);
};

class VA_Color : private VertexAttribute
{
public:
    VA_Color(void);
};

#endif
