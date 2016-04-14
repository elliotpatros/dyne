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
defaultPitch (0.f),
defaultYaw (halfpi),
defaultFov (0.25f * pi),

// non-owned classes
time {Time::getInstance()},
input {Input::getInstance()},
circle {CircleLUT::getInstance()}
{
    // camera properties
    position = defaultPosition;
    front = defaultFront;
    up = defaultUp;
    pitch = defaultPitch;
    yaw = defaultYaw;
    
    distanceFromCenter = glm::distance(vec3(0), position);
    
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
    setDistanceFromCenter(y);
}

void Camera::setDistanceFromCenter(double d) noexcept
{
    distanceFromCenter += d;
    distanceFromCenter = tclip(distanceFromCenter, 50.f, 400.f);
}

void Camera::setRotationSpeed(double s) noexcept
{
    
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
    const GLfloat angle (speed * time.getDelta());
    if (input.getKeyState(GLFW_KEY_W)) {pitch += angle; } // up
    if (input.getKeyState(GLFW_KEY_S)) {pitch -= angle; } // down
    if (input.getKeyState(GLFW_KEY_A)) {yaw   += angle; } // left
    if (input.getKeyState(GLFW_KEY_D)) {yaw   -= angle; } // right
    
    pitch = (pitch < 0.f) ? twopi - fabsf(pitch) : fmodf(pitch, twopi);
    up = ((pitch < halfpi) || (pitch > threehalvespi)) ? defaultUp : -defaultUp;
    position = distanceFromCenter * vec3(circle.cos(pitch) * circle.cos(yaw),
                                         circle.sin(pitch),
                                         circle.cos(pitch) * circle.sin(yaw));
    
    front = -position;
}
