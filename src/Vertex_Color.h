//
//  Vertex_Color.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Vertex_Color__
#define __dyne__Vertex_Color__

#include "VertexAttribute.h"
#include "AssimpBase.h"
#include "GLMBase.h"

class Vertex_Color
{
public:
    
    struct Type
    {
        vec3 position;
        vec3 normal;
        vec3 color;
    };
    
    void enableVertexAttributes(void);
    Type loadVertex(aiMesh* mesh, GLuint vertex) noexcept;
    
    
private:
    static VA_Position vaPosition;
    static VA_Normal vaNormal;
    static VA_Color vaColor;
};

#endif
