//
//  CircleLUT.h
//  dyne
//
//  Created by Elliot Patros on 12/11/15.
//  Copyright (c) 2015 Elliot Patros. All rights reserved.
//

#ifndef dyne_CircleLUT_h
#define dyne_CircleLUT_h

#include "DyneBase.h"
#include <stdlib.h> // for malloc
#include <math.h>
#include "Maths.h"

class CircleLUT
{
public:
    static CircleLUT& getInstance(void)
    {
        static CircleLUT instance;
        return instance;
    }
    
    inline float sin (const float radFreq) const noexcept
    {
        return sineTable[static_cast<unsigned> (nOverTwopi * radFreq) & nMinusOne];
    }
    inline float cos (const float radFreq) const noexcept
    {
        return sineTable[(static_cast<unsigned> (nOverTwopi * radFreq) + cosPhase) & nMinusOne];
    }
    
    
private:
    // singleton stuff
    CircleLUT(void) :
    N(powf(2.f, 16.f) ),
    nOverTwopi(N * rTwopi),
    nMinusOne(unsigned(roundToInt(N) ) - 1),
    cosPhase(unsigned(N/4.f))
    {
        const unsigned uiN = unsigned (N);
        try
        {
            sineTable = (float*)malloc(uiN * sizeof(GLfloat));
            if (sineTable == nullptr)
            {
                throw runtime_error ("sine table failed to initialize");
            }
        }
        catch (exception &e)
        {
            IO::post("caught exception", e.what());
            return;
        }
        
        const float rN = 1.f / N;
        for (unsigned i = 0; i < uiN; ++i)
        {
            sineTable[i] = sinf(twopi * rN * static_cast<float> (i) );
        }
    }
    
    ~CircleLUT(void)
    {
        if (sineTable != nullptr)
        {
            free(sineTable);
            sineTable = nullptr;
        }
    }
    
    CircleLUT(CircleLUT const&);
    void operator=(CircleLUT const&);
    
    const float N;
    const float nOverTwopi;
    const unsigned nMinusOne;
    const unsigned cosPhase;
    
    float* sineTable;
};

#endif
