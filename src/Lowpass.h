//
//  Lowpass.h
//  dyne
//
//  Created by Elliot Patros on 3/31/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__Lowpass__
#define __dyne__Lowpass__

#include "DyneBase.h"
#include "GLMBase.h"
#include "OpenGLBase.h"
#include "Maths.h"

template<typename Type>
class Lowpass
{
public:
    Lowpass(void) {
        setCutoff(0);
        initialize(Type (0));
    }
    
    void initialize(const Type state) noexcept {
        b1 = a1 = state;
    }
    
    void setCutoff(const float cutoff) noexcept {
        const float K {tanf(pi * cutoff)};
        
        cb1 =
        cb0 = K / (K + 1);
        ca1 = (K - 1) / (K + 1);
    }
    
    Type filter(const Type type) noexcept {
        const Type value = cb0 * type + cb1 * b1 - ca1 * a1;
        
        b1 = type;
        a1 = value;
        
        return value;
    }
    
    
private:
    // coefficients
    Type cb0, cb1, ca1;
    
    // state
    Type b1, a1;
};

#endif
