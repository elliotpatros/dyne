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

class VA_Position : public VertexAttribute
{
public:
    VA_Position(const GLuint location);
};

class VA_Normal : public VertexAttribute
{
public:
    VA_Normal(const GLuint location);
};

class VA_Color : public VertexAttribute
{
public:
    VA_Color(const GLuint location);
};

#endif
