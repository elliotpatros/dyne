//
//  Mesh.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Mesh__
#define __dyne__Mesh__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"
#include "AssimpBase.h"

#include "Maths.h"
#include "Shader.h"

struct VertexType
{
    enum Flag
    {
        PositionNormalColor = 0, // position, normal, color
        Position        // position
    };
    
    struct PNC
    {
        vec3 position;
        vec3 normal;
        vec3 color;
    };
    
    struct P
    {
        vec3 position;
    };
};

class Mesh
{
public:
    explicit Mesh(aiMesh* m, VertexType::Flag type);
    
    void drawInstanced(const GLuint nInstances) const noexcept;
    void draw(void) const noexcept;
    
    
private:
    void initialize(VertexType::Flag type);
    void load(aiMesh* m, VertexType::Flag type) noexcept;
    
    void makeColorVertex(aiMesh* m) noexcept;
    void bindColorVertex(void) noexcept;
    void makePositionVertex(aiMesh* m) noexcept;
    void bindPositionVertex(void) noexcept;
    
    GLuint vertexArray, vertexBuffer, elementBuffer;
    GLsizei nIndices;
    GLuint nVertices;
    vector<VertexType::PNC> pncVertices;
    vector<VertexType::P> pVertices;
    vector<GLuint> indices;
};

#endif
