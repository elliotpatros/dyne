//
//  Model.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Model__
#define __dyne__Model__

#include "DyneBase.h"
#include "AssimpBase.h"
#include "Mesh.h"

class Model
{
public:
    void drawInstanced(const GLuint nInstances) const noexcept;
    void draw(void) const noexcept;
    void load(const string path,
              VertexType::Flag type) noexcept;
    
    
private:
    GLuint nMeshes;
    vector<Mesh> meshes;
    
    void processNode(aiNode* node,
                     const aiScene* scene,
                     VertexType::Flag type) noexcept;
};

#endif
