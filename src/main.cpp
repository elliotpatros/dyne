//
//  main.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Application.h"

#include "Physics.h"

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
    Physics p[10];
    pthread_mutex_init(&Physics::lock, NULL);
    
    for (int i = 0; i < 10; ++i)
    {p[i].instance = i; }
    
    for (int i = 0; i < 10; ++i)
    {p[i].startMs(0); }
    
    usleep(1000*20000);
    
    for (int i = 0; i < 10; ++i) {p[i].stop(); }
    
//    makeProjDirCurrentDir();
//    
//    Application& app {Application::getInstance() };
//    if (app.setup()) {return 1; }
//    app.run();
//    
//    return 0;
}
