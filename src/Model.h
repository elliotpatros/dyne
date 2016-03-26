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

template<typename Vertex>
class Model
{
public:
    void draw(void) const noexcept;
    void load(const string path);
    
    
private:
    GLuint nMeshes;
    vector<Mesh<Vertex>> meshes;
    
    void processNode(aiNode* node, const aiScene* scene) noexcept;
    void processMesh(aiMesh* mesh) noexcept;
};

#endif
