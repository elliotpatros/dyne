//
//  Camera.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Camera.h"

GLfloat Camera::distanceFromCenter (0.f);
GLfloat Camera::rotationSpeed (0.f);

//==============================================================================
// init stuff
//==============================================================================
Camera::Camera(void) :
// constants
speed (0.8f),
nearField (0.1f),
farField (1000.0),

// defaults
defaultPosition (0.f, 0.f, 100.f),
defaultFront (0.f, 0.f, -1.f),
defaultUp (0.f, 1.f, 0.f),
defaultPitch (halfpi * 0.125f),
defaultYaw (halfpi),
defaultFov (0.25f * pi),

// non-owned classes
circle {CircleLUT::getInstance()}
{
    // camera properties
    position = defaultPosition;
    front = defaultFront;
    up = defaultUp;
    pitch = defaultPitch;
    yaw = defaultYaw;
    
    distanceFromCenter = glm::distance(vec3(0), position);
    
    glfwSetTime(lastTime = 1);
    
    update();
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
void Camera::handleMouseScroll(GLFWwindow* w, double x, double y) noexcept
{
    distanceFromCenter += y;
    distanceFromCenter = tclip(distanceFromCenter, 50.f, 450.f);
}

void Camera::setDistanceFromCenter(GLfloat d) noexcept
{
    distanceFromCenter = tclip(d, 50.f, 450.f);
}

void Camera::setRotationSpeed(double s) noexcept
{
    rotationSpeed = s;
}

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
    const GLfloat now (glfwGetTime());
    yaw += rotationSpeed * (now - lastTime);
    if      (yaw < -twopi) {yaw += twopi; }
    else if (yaw > twopi)  {yaw -= twopi; }
    
    position = distanceFromCenter * vec3(circle.cos(pitch) * circle.cos(yaw),
                                         circle.sin(pitch),
                                         circle.cos(pitch) * circle.sin(yaw));
    
    front = -position;
    lastTime = now;
}
