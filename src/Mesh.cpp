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
Mesh::Mesh(aiMesh* m)
{
    load(m);
    initialize();
}

void Mesh::load(aiMesh* m) noexcept
{
    // load vertices
    vertices.resize(m->mNumVertices);
    
    for (GLuint vertex = 0; vertex < m->mNumVertices; ++vertex)
    {
        vertices[vertex] = {.position = vec3(m->mVertices[vertex].x,
                                             m->mVertices[vertex].y,
                                             m->mVertices[vertex].z),
                            .normal = vec3(m->mNormals[vertex].x,
                                           m->mNormals[vertex].y,
                                           m->mNormals[vertex].z),
                            .color = vec3(1.f)};
    }
    
    // load indices
    for (GLuint face = 0; face < m->mNumFaces; ++face)
    {
        aiFace aiface(m->mFaces[face]);
        for (GLuint i = 0; i < aiface.mNumIndices; ++i)
        {
            indices.push_back(aiface.mIndices[i]);
        }
    }
}

void Mesh::initialize(void)
{
    nIndices = static_cast<GLsizei>(indices.size());
    
    // generate vbo and ebo
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    
    // generate and bind vao
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    // bind vertex information to vbo and ebo
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(Vertex),
                 &vertices[0],
                 GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 nIndices * sizeof(GLuint),
                 &indices[0],
                 GL_STATIC_DRAW);
    
    // position
    glEnableVertexAttribArray(0);           // location
    glVertexAttribPointer(0,                // location
                          3,                // n values
                          GL_FLOAT,         // default
                          GL_FALSE,         // default
                          sizeof(Vertex),   // stride
                          (GLvoid*)0);      // offset
    
    // normal
    glEnableVertexAttribArray(1);          
    glVertexAttribPointer(1,               
                          3,               
                          GL_FLOAT,        
                          GL_FALSE,        
                          sizeof(Vertex),
                          (GLvoid*)offsetof(Vertex, normal));
    
    // color
    glEnableVertexAttribArray(2);           
    glVertexAttribPointer(2,                
                          3,                
                          GL_FLOAT,         
                          GL_FALSE,         
                          sizeof(Vertex),   
                          (GLvoid*)offsetof(Vertex, color));
    
    glBindVertexArray(0);
}

//==============================================================================
// loop
//==============================================================================
void Mesh::draw(const GLuint nInstances) const noexcept
{
    glBindVertexArray(vertexArray);
    glDrawElementsInstanced(GL_TRIANGLES,
                            nIndices,
                            GL_UNSIGNED_INT,
                            0,
                            nInstances);
    glBindVertexArray(0);
}
