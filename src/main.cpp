//
//  main.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "AssimpBase.h"
#include "FreeTypeBase.h"
#include "GLMBase.h"
#include "OpenGLBase.h"
#include "OSCBase.h"
#include "Maths.h"
#include "Application.h"

/*
 * change application's current directory
 * to project build folder
 */
void makeProjDirCurrentDir(void)
{
    char* baseDir = getenv("HOME");
    const char* appDir = "/Dropbox/dyne";
    chdir(strcat(baseDir, appDir));

}

int main(void)
{
    makeProjDirCurrentDir();
    
    Application& app {Application::getInstance() };
    if (app.setup()) {return 1; }
    app.run();
    
    return 0;
}
