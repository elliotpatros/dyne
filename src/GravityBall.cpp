//
//  GravityBall.cpp
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "GravityBall.h"

vector<GravityBall*> GravityBall::gravityBalls{vector<GravityBall*>()};
Shader GravityBall::shader{"color-body.vs", "color-body.fs"};

GravityBall::GravityBall(void)
{
    load("smooth-iso.obj");
    gravityBalls.push_back(this);
}

void GravityBall::render(void) noexcept
{
    shader.use();
    
    const size_t nBalls = gravityBalls.size();
    for (int i = 0; i < nBalls; ++i)
    {
        gravityBalls[i]->draw();
    }
}
