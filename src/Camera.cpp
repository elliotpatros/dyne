//
//  Camera.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Camera.h"

//==============================================================================
// init stuff
//==============================================================================
Camera::Camera(void) :
// constants
maxPitch{89.0},
speed{20.0},
mouseSensitivity{0.1f},
nearField{0.1f},
farField{1000.0},

// defaults
defaultPosition{0.f, 5.f, 20.f},
defaultFront{0.f, 0.f, -1.f},
defaultUp{0.f, 1.f, 0.f},
defaultPitch{0.f},
defaultYaw{-90.f},
defaultFov{0.25f * pi},

// non-owned classes
time{Time::getInstance()},
input{Input::getInstance()},
circle{CircleLUT::getInstance()}
{
    // camera properties
    position = defaultPosition;
    front = defaultFront;
    up = defaultUp;
    pitch = defaultPitch;
    yaw = defaultYaw;
    
    smoothness = 0.35;
    smoothedX = smoothedY = 0.0;
    firstMouseMove = true;
}

Camera& Camera::getInstance(void)
{
    static Camera instance;
    return instance;
}

//==============================================================================
// gets
//==============================================================================
glm::vec3 Camera::getPosition(void) const noexcept
{
    return position;
}

glm::mat4 Camera::getLookAt(void) const noexcept
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection(void) const noexcept
{
    return projection;
}

glm::mat4 Camera::getProjectionDotLookAt(void) const noexcept
{
    return projection * glm::lookAt(position, position + front, up);
}

//==============================================================================
// sets
//==============================================================================
void Camera::setWindowProperties(GLFWwindow* window, const ivec2 size) noexcept
{
    this->mainWindow = window;
    
    projection = glm::perspective(defaultFov,
                                  (GLfloat)size.x / (GLfloat)size.y,
                                  nearField,
                                  farField);
}

void Camera::update(void) noexcept
{
    glfwGetCursorPos(mainWindow, &mouseX, &mouseY);
    glfwSetCursorPos(mainWindow, 0.0, 0.0);
    
    if (firstMouseMove)
    {
        if ((mouseX != 0.0) || (mouseY != 0.0) )
        {
            firstMouseMove = bool(mouseX = mouseY = 0.0);
        }
    }
    
    smoothedX *= smoothness;
    smoothedY *= smoothness;
    smoothedX += ((mouseX *= (1.0 - smoothness)) += smoothedX);
    smoothedY += ((mouseY *= (1.0 - smoothness)) += smoothedY);
    
    // mouse stuff
    yaw += mouseX * mouseSensitivity;
    pitch -= mouseY * mouseSensitivity;
    pitch = tclip(pitch, -maxPitch, maxPitch);
    
    updateVectors();
    speedNormalized = speed * time.getDelta();
    strafe = glm::normalize(glm::cross(front, up)) * speedNormalized;
    moveForward = front * speedNormalized;
    
    // keyboard stuff
    if (input.getKeyState(GLFW_KEY_W)) {position += moveForward; }
    if (input.getKeyState(GLFW_KEY_S)) {position -= moveForward; }
    if (input.getKeyState(GLFW_KEY_A)) {position -= strafe; }
    if (input.getKeyState(GLFW_KEY_D)) {position += strafe; }
}

void Camera::resetFirstMouse(void) noexcept
{
    if (mainWindow != nullptr)
    {
        glfwSetCursorPos(mainWindow, 0.0, 0.0);
    }
    
    firstMouseMove = true;
}

void Camera::updateVectors(void) noexcept
{
    const GLfloat pitchRadians = glm::radians(pitch);
    const GLfloat yawRadians = glm::radians(yaw);
    glm::vec3 cameraFront(circle.cos(pitchRadians) * circle.cos(yawRadians),
                          circle.sin(pitchRadians),
                          circle.cos(pitchRadians) * circle.sin(yawRadians) );
    
    front = glm::normalize(cameraFront);
}

glm::vec3 Camera::updateStrafe(void) noexcept
{
    return glm::normalize(glm::cross(front, up)) * speedNormalized;
}

glm::vec3 Camera::updateMoveForward(void) noexcept
{
    return front * speedNormalized;
}
