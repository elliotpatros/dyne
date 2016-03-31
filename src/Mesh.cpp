//
//  Mesh.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Mesh.h"

//==============================================================================
// startup
//==============================================================================
Mesh::Mesh(aiMesh* mesh, VertexType::Flag type)
{
    load(mesh, type);
    initialize(type);
}

void Mesh::load(aiMesh* mesh, VertexType::Flag type) noexcept
{
    // load vertices
    nVertices = mesh->mNumVertices;
    
    switch (type)
    {
        case VertexType::PositionNormal:
        {
            makePNVertex(mesh);
            break;
        }
        case VertexType::Position:
        {
            makePVertex(mesh);
            break;
        }
        default:
        {
            break;
        }
    }
    
    // load indices
    for (GLuint face = 0; face < mesh->mNumFaces; ++face)
    {
        aiFace aiface(mesh->mFaces[face]);
        for (GLuint i = 0; i < aiface.mNumIndices; ++i)
        {
            indices.push_back(aiface.mIndices[i]);
        }
    }
}

void Mesh::initialize(VertexType::Flag type)
{
    nIndices = static_cast<GLsizei>(indices.size());
    
    // generate vbo and ebo
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    
    // generate and bind vao
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    // bind element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 nIndices * sizeof(GLuint),
                 &indices[0],
                 GL_STATIC_DRAW);
    
    switch (type)
    {
        case VertexType::PositionNormal:
        {
            bindPNVertex();
            break;
        }
        case VertexType::Position:
        {
            bindPVertex();
            break;
        }
        default:
        {
            break;
        }
    }
    
    glBindVertexArray(0);
}

//==============================================================================
// loop
//==============================================================================
void Mesh::drawInstanced(const GLuint nInstances) const noexcept
{
    glBindVertexArray(vertexArray);
    glDrawElementsInstanced(GL_TRIANGLES,
                            nIndices,
                            GL_UNSIGNED_INT,
                            0,
                            nInstances);
    glBindVertexArray(0);
}

void Mesh::draw(void) const noexcept
{
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES,
                   nIndices,
                   GL_UNSIGNED_INT,
                   0);
    
    glBindVertexArray(0);
}

//==============================================================================
// how I'm going to handle different kinds of vertices for now
//==============================================================================
void Mesh::makePNVertex(aiMesh* m) noexcept
{
    pnVertices.resize(m->mNumVertices);
    
    for (GLuint vertex = 0; vertex < nVertices; ++vertex)
    {
        pnVertices[vertex] =
        {.position = vec3(m->mVertices[vertex].x,
                          m->mVertices[vertex].y,
                          m->mVertices[vertex].z),
         .normal = vec3(m->mNormals[vertex].x,
                        m->mNormals[vertex].y,
                        m->mNormals[vertex].z)
        };
    }
}

void Mesh::bindPNVertex(void) noexcept
{
    // bind vertex information to vbo and ebo
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertices * sizeof(VertexType::PN),
                 &pnVertices[0],
                 GL_STATIC_DRAW);
    // position
    glEnableVertexAttribArray(0);                  // location
    glVertexAttribPointer(0,                       // location
                          3,                       // n values
                          GL_FLOAT,                // default
                          GL_FALSE,                // default
                          sizeof(VertexType::PN),  // stride
                          (GLvoid*)0);             // offset
    
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(VertexType::PN),
                          (GLvoid*)offsetof(VertexType::PN, normal));
}

void Mesh::makePVertex(aiMesh* m) noexcept
{
    pVertices.resize(m->mNumVertices);
    
    for (GLuint vertex = 0; vertex < nVertices; ++vertex)
    {
        pVertices[vertex] =
        {
            vec3(m->mVertices[vertex].x,
                 m->mVertices[vertex].y,
                 m->mVertices[vertex].z)
        };
    }
}

void Mesh::bindPVertex(void) noexcept
{
    // bind vertex information to vbo and ebo
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 nVertices * sizeof(VertexType::P),
                 &pVertices[0],
                 GL_STATIC_DRAW);
    // position
    glEnableVertexAttribArray(0);               
    glVertexAttribPointer(0,                    
                          3,                    
                          GL_FLOAT,             
                          GL_FALSE,             
                          sizeof(VertexType::P),
                          (GLvoid*)0);
}
