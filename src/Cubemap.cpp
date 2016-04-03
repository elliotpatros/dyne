//
//  CubeMap.cpp
//  dyne
//
//  Created by Elliot Patros on 3/28/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "CubeMap.h"

// glsl uniform locations
GLuint CubeMap::viewLoc{0};
//GLuint CubeMap::skyboxLoc{0};
GLuint CubeMap::textureID{0};

// shader, sphere model and camera
Shader CubeMap::shader{Shader()};
Model CubeMap::model{Model()};
Camera& CubeMap::camera{Camera::getInstance()};

// face names
const string CubeMap::faceNames[6] {"_right", "_left",
                                    "_top", "_bottom",
                                    "_back", "_front"};

void CubeMap::setup(void) noexcept
{
    // load shader and model
    shader = Shader("CubeMap.vs", "CubeMap.fs");
    model.load("skybox.obj", VertexType::Position);
    
    // get shader uniform info
    const GLuint id{shader.useAndGetId()};
    
    viewLoc = glGetUniformLocation(id, "view");
    
    glUniformMatrix4fv(glGetUniformLocation(id, "projection"), 1, GL_FALSE,
                       glm::value_ptr(camera.getProjection()));
    
    // load textures
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    GLuint width, height;
    vector<vector<unsigned char>> image (6);
    for (GLuint i = 0; i < image.size(); ++i)
    {
        const string filename {"resources/textures/test.png"}; // cube2" + faceNames[i] + ".png"};
        unsigned error = lodepng::decode(image[i],
                                         width,
                                         height,
                                         filename);
        
        if (error)
        {
            IO::post("lodepng error ", error, ": ", lodepng_error_text(error));
        }
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                     width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[i][0]);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::render(void) noexcept
{
    glFrontFace(GL_CW);
    glDepthFunc(GL_LEQUAL);
    shader.use();
    
    // update camera
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE,
                       glm::value_ptr(camera.getLookAt()));
//                       glm::value_ptr(mat4(mat3(camera.getLookAt()))));
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    model.draw();
    
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
}
