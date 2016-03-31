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
        PositionNormal = 0, // position, normal
        Position            // position
    };
    
    struct PN
    {
        vec3 position;
        vec3 normal;
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
    
    void makePNVertex(aiMesh* m) noexcept;
    void bindPNVertex(void) noexcept;
    void makePVertex(aiMesh* m) noexcept;
    void bindPVertex(void) noexcept;
    
    GLuint vertexArray, vertexBuffer, elementBuffer;
    GLsizei nIndices;
    GLuint nVertices;
    vector<VertexType::PN> pnVertices;
    vector<VertexType::P> pVertices;
    vector<GLuint> indices;
};

#endif
