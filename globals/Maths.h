//
//  Maths.h
//  dyne
//
//  Created by Elliot Patros on 12/11/15.
//  Copyright (c) 2015 Elliot Patros. All rights reserved.
//

#ifndef dyne_Maths_h
#define dyne_Maths_h

#include <math.h>
#include "OpenGLBase.h"

//==============================================================================
// limits
//==============================================================================
const float dyne_epsilon {std::numeric_limits<float>::epsilon()};

//==============================================================================
// comparisons
//==============================================================================
template <typename Type>
inline Type tmin(const Type a, const Type b) noexcept {
    return (b < a) ? b : a;
}

template <typename Type>
inline Type tmax(const Type a, const Type b) noexcept {
    return (a < b) ? b : a;
}
template <typename Type>
inline Type tmax(const Type a, const Type b, const Type c) noexcept {
    return (a < b) ? ((b < c) ? c : b) : ((a < c) ? c : a);
}

template <typename Type>
inline Type tclip(const Type val, const Type min, const Type max) noexcept {
    return (val < min) ? min : (tmin(val, max) );
}

inline bool isOdd(const int x) noexcept {return static_cast<bool> (x & 1); }

inline bool isZero(const float x) noexcept {return fabsf(x) < dyne_epsilon; }

//==============================================================================
// conversions
//==============================================================================
inline float msToHz(const float ms) noexcept {
    return 1000.f / ms;
}

inline float hzToMs(const float hz) noexcept {
    return 1000.f / hz;
}

//==============================================================================
// rounding
//==============================================================================
inline int roundToInt(const float i) noexcept {
    return static_cast<int> (floorf (i + 0.5f) );
}

inline int floorToInt(const float i) noexcept {
    return static_cast<int> (floorf (i) );
}

//==============================================================================
// random
//==============================================================================
const float rIntMax = 1.f / float(INT_MAX);

inline float getRandomBetween(float min, float max) noexcept {
    return float (rand()) * rIntMax * (max - min) + min;
}

inline int getRandomIntBetween(int min, int max) noexcept {
    return floorToInt(getRandomBetween(float(min), float(max)));
}
                             
//==============================================================================
// pies
//==============================================================================
const float pi {3.1415926535897932384626433832795f};
const float twopi {2.f * pi};
const float halfpi {0.5f * pi};
const float threehalvespi {1.5f * pi};
const float rTwopi {1.f / twopi};

#endif




























