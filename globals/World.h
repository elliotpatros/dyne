//
//  World.h
//  dyne
//
//  Created by Elliot Patros on 12/11/15.
//  Copyright (c) 2015 Elliot Patros. All rights reserved.
//

#ifndef dyne_WorldDimensions_h
#define dyne_WorldDimensions_h

#include "OpenGLBase.h"


class World
{
public:
    static World& getInstance (void)
    {
        static World instance;
        return instance;
    }
    
    // gets
    GLfloat getWindowWidthPixels (void) const noexcept
    {
        return windowWidthPixels;
    }
    
    GLfloat getWindowHeightPixels (void) const noexcept
    {
        return windowHeightPixels;
    }
    
    GLfloat getRWindowWidthPixels (void) const noexcept
    {
        return rwindowWidthPixels;
    }
    
    GLfloat getRWindowHeightPixels (void) const noexcept
    {
        return rwindowHeightPixels;
    }
    
    GLfloat getAspectRatio (void) const noexcept
    {
        return aspectRatio;
    }
    
    GLfloat getRAspectRatio (void) const noexcept
    {
        return rAspectRatio;
    }
    
    GLfloat getStartTime (void) const noexcept
    {
        return startTime;
    }
    
    // sets
    void setWindowSizePixels (const GLfloat width, const GLfloat height) noexcept
    {
        windowWidthPixels = width;
        windowHeightPixels = height;
        rwindowWidthPixels = 1.f / windowWidthPixels;
        rwindowHeightPixels = 1.f / windowHeightPixels;
        aspectRatio = windowWidthPixels / windowHeightPixels;
        rAspectRatio = windowHeightPixels / windowWidthPixels;
        
        const float wMinusOne = windowWidthPixels - 1.f;
        const float hMinusOne = windowHeightPixels - 1.f;
        toGLXPos = 2.f / wMinusOne;
        toGLYPos = -2.f / hMinusOne;
        toPixXPos = wMinusOne / 2.f;
        toPixYPos = hMinusOne / -2.f;
    }
    
    // conversions
    GLfloat xPixelToGL (const GLfloat xPixel) const noexcept
    {
        return xPixel * toGLXPos - 1.f;
    }
    
    GLfloat yPixelToGL (const GLfloat yPixel) const noexcept
    {
        return yPixel * toGLYPos + 1.f;
    }
    
    GLfloat xGLToPixel (const GLfloat xGL) const noexcept
    {
        return (xGL + 1.f) * toPixXPos;
    }
    
    GLfloat yGLToPixel (const GLfloat yGL) const noexcept
    {
        return (yGL - 1.f) * toPixYPos;
    }
    
private:
    // singleton stuff
    World (void) :
    startTime {1}
    {
//        setWindowSizePixels (400, 300);
        setWindowSizePixels (800, 600);
    }
    World (World const&);
    void operator= (World const&);
    
    // sizes in pixels
    GLfloat windowWidthPixels, windowHeightPixels;
    GLfloat rwindowWidthPixels, rwindowHeightPixels;
    GLfloat aspectRatio, rAspectRatio;
    GLfloat toGLXPos, toGLYPos, toPixXPos, toPixYPos;
    //\sizes in pixels
    
    // sizes in mm
    //\sizes in mm
    
    const GLfloat startTime;
    /*
     * maybe we could use mm instead of pixels
     */
};

#endif
