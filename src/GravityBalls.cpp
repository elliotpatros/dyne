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
GLuint GravityBalls::viewPosLoc{0};
GLuint GravityBalls::projectionLoc{0};
GLuint GravityBalls::modelLoc[DYNE_MAX_INSTANCES]{0};

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
    sphere.load("smooth-iso.obj");
    
    const GLuint id{shader.useAndGetId()};
    viewPosLoc = glGetUniformLocation(id, "viewPos");
    projectionLoc = glGetUniformLocation(id, "projection");
    
    for (int i = 0; i < DYNE_MAX_INSTANCES; ++i)
    {
        modelLoc[i] = glGetUniformLocation(id,
                      ("model[" + std::to_string(i) + "]").c_str());
    }
    
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
void GravityBalls::render(void) noexcept
{
    shader.use();
    
    // update camera
    const vec3 viewPos{camera.getPosition()};
    glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                       glm::value_ptr(camera.getProjection()));
    
    // update model
    for (GLuint i = 0; i < nBalls; ++i)
    {
        mat4 model{glm::translate(mat4(), vec3(i%10, 0, (int)i/10))};
        model = glm::scale(model, vec3(getRandomBetween(0.5f, 0.6f)));
        
        glUniformMatrix4fv(modelLoc[i], 1, GL_FALSE,
                           glm::value_ptr(model));
    }
    
    sphere.draw(nBalls);
}
