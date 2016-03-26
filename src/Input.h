//
//  Input.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Input__
#define __dyne__Input__

#include "DyneBase.h"
#include "OpenGLBase.h"
#include "GLMBase.h"

class Input
{
public:
    typedef void(*Callback)(void);
    
    static Input& getInstance(void);
    static void keyPressed(GLFWwindow* window,
                           int key,
                           int scancode,
                           int action,
                           int mode);
    
    // sets
    bool registerKeyCallback(Callback callback, int key) noexcept;
    bool unregisterKeyCallback(int key) noexcept;
    // gets
    bool getKeyState(GLuint key) const noexcept;
    void handleFirstPresses(void) const noexcept;
    
    // callback stuff
    static void nullCallback(void) {}
    
    
private:
    // singleton stuff
    Input(void);
    Input(Input const&);
    void operator= (Input const&);
    
    // handles key presses
    const unsigned nKeys;
    unique_ptr<vector<bool>> keyStates;
    unique_ptr<vector<int>> firstKeyPresses;
    
    void handleKeyPress(int key,
                        int scancode,
                        int action,
                        int mode) noexcept;
    
    
    // callback stuff
    unique_ptr<vector<Callback>> callbacks;
};

#endif
