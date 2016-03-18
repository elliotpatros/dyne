//
//  main.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "DyneBase.h"
#include "AssimpBase.h"
#include "FreeTypeBase.h"
#include "GLMBase.h"
#include "OpenGLBase.h"
#include "OSCBase.h"

#include <unistd.h> // for chdir

int main(int argc, const char* argv[])
{
    // change application's current directory to project build folder
    chdir(string(string(getenv("HOME")) + "/Dropbox/dyne").c_str());
    
    
    cout << "we made it!\n";
    return 0;
}
