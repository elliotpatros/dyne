//
//  GravityBall.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "GravityBall.h"

//==============================================================================
// initialize static members
//==============================================================================
// glsl uniform locations
GLuint GravityBall::viewPosLoc{0};
GLuint GravityBall::lookAtLoc{0};
GLuint GravityBall::transformLoc{0};

// shader, model and camera
Shader GravityBall::shader{Shader()};
Model GravityBall::model{Model()};
Camera& GravityBall::camera{Camera::getInstance()};

// all balls
vector<GravityBall*> GravityBall::gravityBalls{vector<GravityBall*>()};


//==============================================================================
// start up
//==============================================================================
GravityBall::GravityBall(void)
{
    gravityBalls.push_back(this);
}

void GravityBall::setup(void) noexcept
{
    shader = Shader("color-body.vs", "color-body.fs");
    model.load("smooth-iso.obj");
    
    const GLuint id(shader.useAndGetId());
    viewPosLoc = glGetUniformLocation(id, "viewPos");
    lookAtLoc = glGetUniformLocation (id, "lookAt");
    transformLoc = glGetUniformLocation (id, "model");
    
    glUniform3f(glGetUniformLocation(id, "light.position"), 10.f, 10.f, 10.f);
    glUniform3f(glGetUniformLocation(id, "light.ambient"), 0.5f, 0.48f, 0.51f);
    glUniform3f(glGetUniformLocation(id, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(id, "light.specular"), 0.4f, 0.4f, 0.4f);
    glUniform1f(glGetUniformLocation(id, "light.linear"), 0.022f);
    glUniform1f(glGetUniformLocation(id, "light.quadratic"), 0.0019f);
    glUniform1f(glGetUniformLocation(id, "light.shininess"), 32.f);
    glUniformMatrix4fv(glGetUniformLocation(id, "projection"),
                       1,
                       GL_FALSE,
                       glm::value_ptr(camera.getProjection()));
}

//==============================================================================
// loop
//==============================================================================
void GravityBall::render(void) noexcept
{
    shader.use();
    updateCamera();
    
    const size_t nBalls = gravityBalls.size();
    for (int i = 0; i < nBalls; ++i)
    {
        gravityBalls[i]->updateGraphics();
        model.draw();
    }
}

void GravityBall::updateCamera(void) noexcept
{
    const vec3 viewPos(camera.getPosition());
    glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
    glUniformMatrix4fv(lookAtLoc, 1, GL_FALSE, glm::value_ptr(camera.getLookAt()));
}

void GravityBall::updateGraphics(void) noexcept
{
    transform = glm::translate(mat4(), vec3(getRandomBetween(-10.f, 10.f),
                                            getRandomBetween(-10.f, 10.f),
                                            getRandomBetween(-10.f, 10.f)));
    transform = glm::scale(transform, vec3(getRandomBetween(0.f, 1.f)));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}
