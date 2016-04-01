//
//  Camera.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Camera__
#define __dyne__Camera__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"

#include "Maths.h"
#include "CircleLUT.h"
#include "Lowpass.h"

#include "Time.h"
#include "Input.h"

class Camera
{
public:
    static Camera& getInstance(void);
    
    // gets
    glm::vec3 getPosition(void) const noexcept;
    glm::mat4 getLookAt(void) const noexcept;
    glm::mat4 getProjection(void) const noexcept;
    glm::mat4 getProjectionDotLookAt(void) const noexcept;
    
    // sets
    void setWindowProperties(GLFWwindow* window, const ivec2 size) noexcept;
    void update(void) noexcept;
    static void setDistanceFromCenter(GLFWwindow* w, double x, double y) noexcept;
    
    
private:
    // singleton stuff
    Camera(void);
    Camera(Camera const&);
    void operator= (Camera const&);

    // camera properties
    static GLfloat distanceFromCenter;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    GLfloat pitch;
    GLfloat yaw;
    GLfloat speedNormalized;
    
    // constants
    const GLfloat speed;
    const GLfloat nearField, farField;
    
    // defaults
    const glm::vec3 defaultPosition;
    const glm::vec3 defaultFront;
    const glm::vec3 defaultUp;
    const GLfloat defaultPitch;
    const GLfloat defaultYaw;
    const GLfloat defaultFov;
    
    // non-owned classes
    Time& time;
    Input& input;
    CircleLUT& circle;
    Lowpass<GLfloat> pitchLP, yawLP;
    
    GLFWwindow* mainWindow;
};

#endif
