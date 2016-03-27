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
GLuint GravityBall::projectionLoc{0};
GLuint GravityBall::modelLoc[DYNE_MAX_INSTANCES]{0};

// shader, sphere model and camera
Shader GravityBall::shader{Shader()};
Model GravityBall::sphere{Model()};
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
    sphere.load("smooth-iso.obj");
    
    const GLuint id{shader.useAndGetId()};
    viewPosLoc = glGetUniformLocation(id, "viewPos");
    projectionLoc = glGetUniformLocation(id, "projection");
    
    for (int i = 0; i < DYNE_MAX_INSTANCES; ++i)
    {
        modelLoc[i] = glGetUniformLocation(id,
                      ("model[" + std::to_string(i) + "]").c_str());
        IO::post("model loc ", i, " = ", modelLoc[i]);
    }
    
    IO::post("nBalls = ", gravityBalls.size());
    
    glUniform3f(glGetUniformLocation(id, "light.position"), 10.f, 10.f, 10.f);
    glUniform3f(glGetUniformLocation(id, "light.ambient"), 0.5f, 0.48f, 0.51f);
    glUniform3f(glGetUniformLocation(id, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(id, "light.specular"), 0.4f, 0.4f, 0.4f);
    glUniform1f(glGetUniformLocation(id, "light.linear"), 0.022f);
    glUniform1f(glGetUniformLocation(id, "light.quadratic"), 0.0019f);
    glUniform1f(glGetUniformLocation(id, "light.shininess"), 32.f);
}

//==============================================================================
// loop
//==============================================================================
void GravityBall::render(void) noexcept
{
    shader.use();
    
    // update camera
    const vec3 viewPos{camera.getPosition()};
    glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                       glm::value_ptr(camera.getProjection()));
    
    const float f{5};
    
    // update model
    const GLuint nBalls = (GLuint)gravityBalls.size();
    for (GLuint i = 0; i < nBalls; ++i)
    {
        mat4 model{glm::translate(mat4(), vec3(getRandomBetween(-f, f),
                                               getRandomBetween(-f, f),
                                               getRandomBetween(-f, f)))};
        model = glm::scale(model, vec3(getRandomBetween(-f, f)));
        
        glUniformMatrix4fv(modelLoc[i], 1, GL_FALSE,
                           glm::value_ptr(model));
    }
    
    sphere.draw(nBalls);
}
