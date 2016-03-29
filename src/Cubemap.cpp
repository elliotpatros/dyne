//
//  Cubemap.cpp
//  dyne
//
//  Created by Elliot Patros on 3/28/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Cubemap.h"

// shader, sphere model and camera
Shader Cubemap::shader{Shader()};
Model Cubemap::model{Model()};
Camera& Cubemap::camera{Camera::getInstance()};

void Cubemap::setup(void) noexcept
{
    // load shader and model
    shader = Shader("cubemap.vs", "cubemap.fs");
    model.load("cube.obj");
    
    // get shader uniform info
    const GLuint id{shader.useAndGetId()};
    
    
    // load textures
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    GLuint width, height;
    vector<unsigned char> image;
    for (GLuint i = 0; i < 6; ++i)
    {
        lodepng::decode(image,
                        width,
                        height,
                        "resources/textures/sky" + std::to_string(i) + ".png");
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     &image[0]);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Cubemap::render(void) noexcept
{
    glDepthMask(GL_FALSE);
    shader.use();
    
    // set view and projection matrix
    
//    glBindVertexArray(vao);
}
