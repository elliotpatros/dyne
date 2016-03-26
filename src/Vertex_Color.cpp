//
//  Vertex_Color.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Vertex_Color.h"

VA_Position Vertex_Color::vaPosition{VA_Position(0)};
VA_Normal Vertex_Color::vaNormal{VA_Normal(1)};
VA_Color Vertex_Color::vaColor{VA_Color(2)};

void Vertex_Color::enableVertexAttributes(void)
{
    vaPosition.enable(sizeof(Type), 0);
    vaNormal.enable(sizeof(Type), offsetof(Type, normal));
    vaColor.enable(sizeof(Type), offsetof(Type, color));
}

Vertex_Color::Type Vertex_Color::loadVertex(aiMesh* m, GLuint i) noexcept
{
    return {.position = vec3(m->mVertices[i].x,
                             m->mVertices[i].y,
                             m->mVertices[i].z),
            .normal = vec3(m->mNormals[i].x,
                           m->mNormals[i].y,
                           m->mNormals[i].z),
            .color = vec3(1.f, 1.f, 1.f) };
}