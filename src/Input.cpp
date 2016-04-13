//
//  Input.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Input.h"

#include "Input.h"

Input::Input(void) :
nKeys (GLFW_KEY_LAST + 1),
keyStates {new vector<bool>(nKeys)},
firstKeyPresses {new vector<int>()},
callbacks {new vector<Callback>(nKeys, nullCallback)}
{
    firstKeyPresses->reserve(nKeys);
    
    for (unsigned i = 0; i < nKeys; ++i) {(*keyStates) [i] = false; }
}

Input& Input::getInstance(void)
{
    static Input instance;
    return instance;
}

//==============================================================================
// keyboard gets
//==============================================================================
bool Input::getKeyState(unsigned key) const noexcept
{
    return (*this->keyStates) [key];
}

void Input::handleFirstPresses(void) const noexcept
{
    const size_t nFirstPresses = firstKeyPresses->size();
    for (size_t i = 0; i < nFirstPresses; ++i)
    {
        (*callbacks) [(*firstKeyPresses)[i]]();
    }
    
    if (nFirstPresses > 0)
    {
        firstKeyPresses->clear();
    }
}

//==============================================================================
// keyboard handling
//==============================================================================
void Input::keyPressed(GLFWwindow* window,
                       int key,
                       int scancode,
                       int action,
                       int mode)
{
    getInstance().handleKeyPress(key,
                                 scancode,
                                 action,
                                 mode);
}

void Input::handleKeyPress(int key,
                           int scancode,
                           int action,
                           int mode) noexcept
{
    // record keys that are currently pressed
    if (key != GLFW_KEY_UNKNOWN)
    {
        // pressed and held
        (*keyStates) [key] = (action != GLFW_RELEASE);
        
        // pressed
        if ((action == GLFW_PRESS) && (nKeys > firstKeyPresses->size() ))
        {
            firstKeyPresses->push_back(key);
        }
    }
}

//==============================================================================
// keyboard sets
//==============================================================================
bool Input::registerKeyCallback(Callback callback, int key) noexcept
{
    if (key < nKeys && key >= 0)
    {
        (*callbacks) [key] = callback;
        return true;
    }
    else
    {
        return false;
    }
}

bool Input::unregisterKeyCallback(int key) noexcept
{
    if (key < nKeys && key >= 0)
    {
        (*callbacks) [key] = nullCallback;
        return true;
    }
    else
    {
        return false;
    }
}
