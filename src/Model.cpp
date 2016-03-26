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
void Model::draw(void) const noexcept
{
    for (GLuint i = 0; i < nMeshes; ++i) {meshes[i].draw(); }
}

//==============================================================================
// load
//==============================================================================
void Model::load(const string path) noexcept
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("/Users/empco/Dropbox/dyne/resources/" + path,
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

void Model::processNode(aiNode* node, const aiScene* scene) noexcept
{
    for (GLuint i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh));
        meshes.back().initialize();
    }
    
    for (GLuint i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* aimesh) noexcept
{
    Mesh mesh;
    mesh.loadVertices(aimesh);
    mesh.loadIndices(aimesh);
    
    return mesh;
}
