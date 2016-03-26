//
//  VertexAttribute.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "VertexAttribute.h"

void VertexAttribute::enable(const GLsizei stride,
                             const size_t offset) const noexcept
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer
    (location, nValues, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
}

VA_Position::VA_Position(void)
{
    nValues = 3;
    name = "position";
}

VA_Normal::VA_Normal(void)
{
    nValues = 3;
    name = "normal";
}

VA_Color::VA_Color(void)
{
    nValues = 3;
    name = "color";
}