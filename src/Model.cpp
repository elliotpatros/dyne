//
//  Model.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Model.h"

//==============================================================================
// loop
//==============================================================================
void Model::drawInstanced(const GLuint nInstances) const noexcept
{
    for (GLuint i = 0; i < nMeshes; ++i)
    {
        meshes[i].drawInstanced(nInstances);
    }
}

void Model::draw(void) const noexcept
{
    for (GLuint i = 0; i < nMeshes; ++i)
    {
        meshes[i].draw();
    }
}

//==============================================================================
// load
//==============================================================================
void Model::load(const string path,
                 VertexType::Flag type) noexcept
{
    Assimp::Importer importer;
    const aiScene* scene (importer.ReadFile("resources/obj/" + path,
                                            aiProcess_Triangulate |
                                            aiProcess_JoinIdenticalVertices));
    
    if ((scene == nullptr) ||
        (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) ||
        (scene->mRootNode == nullptr))
    {
        IO::post("ERROR::ASSIMP::", importer.GetErrorString());
        return;
    }
    
    processNode(scene->mRootNode, scene, type);
    nMeshes = static_cast<GLuint>(meshes.size());
}

void Model::processNode(aiNode* node,
                        const aiScene* scene,
                        VertexType::Flag type) noexcept
{
    for (GLuint i = 0; i < node->mNumMeshes; ++i)
    {
        meshes.emplace_back(scene->mMeshes[node->mMeshes[i]], type);
    }
    
    for (GLuint i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene, type);
    }
}
