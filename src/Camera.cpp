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
speed {0.8f},
nearField {0.1f},
farField {1000.0},

// defaults
defaultPosition {0.f, 0.f, 50.f},
defaultFront {0.f, 0.f, -1.f},
defaultUp {0.f, 1.f, 0.f},
defaultPitch {0.f},
defaultYaw {-halfpi},
defaultFov {0.25f * pi},

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
    const float angle {speed * time.getDelta()};
    if (input.getKeyState(GLFW_KEY_W)) {pitch += angle; } // up
    if (input.getKeyState(GLFW_KEY_S)) {pitch -= angle; } // down
    if (input.getKeyState(GLFW_KEY_A)) {yaw   += angle; } // left
    if (input.getKeyState(GLFW_KEY_D)) {yaw   -= angle; } // right
    
    pitch = fmodf(((pitch < 0.f) ? twopi - fabsf(pitch) : pitch), twopi);
    up = ((pitch < halfpi) || (pitch > threehalvespi)) ? defaultUp : -defaultUp;
    position = distanceFromCenter * vec3(circle.cos(pitch) * circle.cos(yaw),
                                         circle.sin(pitch),
                                         circle.cos(pitch) * circle.sin(yaw));
    
    front = -position;
}
