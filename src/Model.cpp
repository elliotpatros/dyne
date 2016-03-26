//
//  Model.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Model.h"

template<typename Vertex>
Model<Vertex>::Model(void)
{
    
}

//==============================================================================
// loop
//==============================================================================
template<typename Vertex>
void Model<Vertex>::draw(void) const noexcept
{
    for (GLuint i = 0; i < nMeshes; ++i) {meshes[i].draw(); }
}

//==============================================================================
// load
//==============================================================================
template<typename Vertex>
void Model<Vertex>::load(const string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("resources/" + path,
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices);
    
    if ((scene == nullptr) ||
        (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) ||
        (scene->mRootNode == nullptr))
    {
        IO::post("ERROR::ASSIMP::", importer.GetErrorString());
        return;
    }
    
    processNode(scene->mRootNode, scene);
    nMeshes = static_cast<GLuint>(meshes.size());
}

template<typename Vertex>
void Model<Vertex>::processNode(aiNode* node, const aiScene* scene) noexcept
{
    for (GLuint i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(this->processMesh(mesh));
        meshes.back().initialize();
    }
}

template<typename Vertex>
void Model<Vertex>::processMesh(aiMesh* aimesh) noexcept
{
    Mesh<Vertex> mesh;
    mesh.enableVertexAttributes(aimesh);
    mesh.loadIndices(aimesh);
    
    return mesh;
}