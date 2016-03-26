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

#include "Shader.h"

template<class Vertex>
class Mesh
{
public:
    Mesh(void);
    
    void draw(void) const noexcept;
    void initialize(void);
    
    void loadVertices(aiMesh* m) noexcept;
    void loadIndices(aiMesh* m) noexcept;
    
private:
    GLuint vertexArray, vertexBuffer, elementBuffer;
    GLsizei nIndices;
    vector<typename Vertex::Type> vertices;
    vector<GLuint> indices;
};

#endif
