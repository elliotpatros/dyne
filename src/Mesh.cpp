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
template<class Vertex>
Mesh<Vertex>::Mesh(void)
{
    
}

template<class Vertex>
void Mesh<Vertex>::initialize(void)
{
    nIndices = static_cast<GLsizei>(indices.size());
    
    // generate vbo and ebo
    glGenBuffers(1, vertexBuffer);
    glGenBuffers(1, elementBuffer);
    
    // generate and bind vao
    glGenVertexArrays(1, vertexArray);
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
    
    enableVertexAttributes();
    glBindVertexArray(0);
}

//==============================================================================
// loop
//==============================================================================
template<class Vertex>
void Mesh<Vertex>::draw(void) const noexcept
{
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
