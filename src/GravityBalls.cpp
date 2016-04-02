//
//  GravityBalls.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "GravityBalls.h"

//==============================================================================
// initialize static members
//==============================================================================
// glsl uniform locations
GLuint GravityBalls::viewPosLoc {0};
GLuint GravityBalls::projectionLoc {0};
GLuint GravityBalls::modelLoc[DYNE_MAX_GBALLS] {0};
GLuint GravityBalls::colorLoc[DYNE_MAX_GBALLS] {0};

// shader, sphere model and camera
Shader GravityBalls::shader{Shader()};
Model GravityBalls::sphere{Model()};
Camera& GravityBalls::camera{Camera::getInstance()};


//==============================================================================
// start up
//==============================================================================
GravityBalls::GravityBalls(void)
{
    nBalls = 0;
}

void GravityBalls::setup(const GLuint nBallsAtStart) noexcept
{
    nBalls = nBallsAtStart;
    shader = Shader("color-body.vs", "color-body.fs");
    sphere.load("smooth-iso.obj", VertexType::PositionNormal);
    
    const GLuint id{shader.useAndGetId()};
    viewPosLoc = glGetUniformLocation(id, "viewPos");
    projectionLoc = glGetUniformLocation(id, "projection");
    
//    skyboxLoc = glGetUniformLocation(id, "skybox");
    
    for (int i = 0; i < DYNE_MAX_GBALLS; ++i)
    {
        const string sindex {std::to_string(i)};
        modelLoc[i] = glGetUniformLocation(id,
                      ("model[" + sindex + "]").c_str());
        colorLoc[i] = glGetUniformLocation(id,
                      ("color[" + sindex + "]").c_str());
        
        glUniform3f(colorLoc[i], getRandomBetween(0.f, 1.f),
                                 getRandomBetween(0.f, 1.f),
                                 getRandomBetween(0.f, 1.f));
    }
    
    glUniform3f(glGetUniformLocation(id, "light.position"),  30.f, 15.f, 30.f);
    glUniform1f(glGetUniformLocation(id, "light.ambient"),   0.9f); //0.19225f);
    glUniform1f(glGetUniformLocation(id, "light.diffuse"),   0.4f); //0.50754f);
    glUniform1f(glGetUniformLocation(id, "light.specular"),  0.774597f); //0.508273f);
    glUniform1f(glGetUniformLocation(id, "light.linear"),    0.007f);
    glUniform1f(glGetUniformLocation(id, "light.quadratic"), 0.0002f);
    glUniform1f(glGetUniformLocation(id, "light.shininess"), 4.f);
    
    
    physics.setup(nBallsAtStart);
}

void GravityBalls::startPhysics(void) noexcept
{
    physics.start();
}

//==============================================================================
// loop
//==============================================================================
void GravityBalls::render(void) noexcept
{
    shader.use();
    
    // update camera
    const vec3 viewPos{camera.getPosition()};
    glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                       glm::value_ptr(camera.getProjectionDotLookAt()));
    
    // update active texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMap::textureID);
    
    // lock masses (wait if busy)
    pthread_mutex_lock(&physics.lock);

    for (GLuint n = 0; n < nBalls; ++n)
    {
        // update model
        mat4 model {glm::translate(mat4(), physics.masses[n].position)};
        model = glm::scale(model, vec3(physics.masses[n].radius));
        glUniformMatrix4fv(modelLoc[n], 1, GL_FALSE, glm::value_ptr(model));
    }
    
    pthread_mutex_unlock(&physics.lock);
    
    // draw everything
    sphere.drawInstanced(nBalls);
}
