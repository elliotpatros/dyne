//
//  main.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Application.h"

int main(void)
{
    chdir(strcat(getenv("HOME"), "/Dropbox/dyne"));
    
    Application& app (Application::getInstance());
    if (app.setup()) {return 1; }
    app.run();
    
    return 0;
}
