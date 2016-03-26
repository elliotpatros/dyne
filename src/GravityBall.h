//
//  GravityBall.h
//  dyne
//
//  Created by Elliot Patros on 3/25/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__GravityBall__
#define __dyne__GravityBall__

#include "DyneBase.h"

#include "Vertex_Color.h"
#include "Model.h"
#include "Shader.h"

class GravityBall : public Model<Vertex_Color>
{
public:
    GravityBall(void);
    
    static void render(void) noexcept;
    
    
private:
    static vector<GravityBall*> gravityBalls;
    static Shader shader;
};

#endif
