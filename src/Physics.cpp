//
//  Physics.cpp
//  dyne
//
//  Created by emp on 3/30/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "Physics.h"

//==============================================================================
// static variables
//==============================================================================


// gravity
float Physics::clockHz {200.f};
const GLfloat Physics::gravityConstant {6.67408f * powf(10.f, -11.f) };
GLfloat Physics::gravityScaler {1000000.f};
GLfloat Physics::gravity {gravityConstant * gravityScaler};
Time& Physics::time {Time::getInstance() };

//==============================================================================
// constructor and destructor
//==============================================================================
Physics::Physics(void) {}

Physics::~Physics(void) {}

//==============================================================================
// public functions
//==============================================================================
void Physics::setNMasses(const size_t n)
{
    masses.resize(n);
    nMasses = (n == 0) ? 0 : masses.size();
    nMassesMinusOne = nMasses - 1;
    
    const float pos = 5.f;
    for (size_t i = 0; i < nMasses; ++i)
    {
        masses[i].position = vec3(getRandomBetween(-pos, pos),
                                  getRandomBetween(-pos, pos),
                                  getRandomBetween(-pos, pos));
    }
}

void Physics::setup(const size_t nMassesAtStart)
{
    setHz(clockHz);
    setNMasses(nMassesAtStart);
    
    pthread_mutex_init(&lock, NULL);
}

//==============================================================================
// threaded physics update
//==============================================================================
void Physics::timerCallback(void) noexcept
{
    // get time variables
    const GLfloat tDelta{time.getDelta()};
    const GLfloat tHalfDeltaSq{time.getHalfDeltaSq()};
    const GLfloat rTDelta{1.f / tDelta};
    
    // reset displacement
    for (size_t i = 0; i < nMasses; ++i) {masses[i].displacement = vec3(0.f);}
    
    pthread_mutex_lock(&lock);
    accumulateDisplacement(tDelta, tHalfDeltaSq);
    moveMasses(rTDelta);
    pthread_mutex_unlock(&lock);
}

//==============================================================================
// physics helper functions
//==============================================================================
void Physics::accumulateDisplacement(const GLfloat tDelta,
                                     const GLfloat tHalfTDeltaSq) noexcept
{
    for (size_t a = 0; a < nMassesMinusOne; ++a)
    {
        const GLfloat ATimesGravity {gravity * masses[a].mass};
        
        for (size_t b = a + 1; b < nMasses; ++b)
        {
            const vec3 AB {masses[b].position - masses[a].position};
            const GLfloat r2 {AB.x * AB.x + AB.y * AB.y + AB.z * AB.z};
            const GLfloat F {ATimesGravity * masses[b].mass / r2};
            masses[a].displacement += (F / masses[a].mass) * AB;
            masses[b].displacement += (F / masses[b].mass) * -AB;
        }
    }
    
    for (size_t i = 0; i < nMasses; ++i)
    {
        // make a gravitational center without size
        const vec3 d {-masses[i].position};
        const GLfloat r2 {tmax (d.x * d.x + d.y * d.y + d.z * d.z, 10.f) };
        const GLfloat F {gravity * masses[i].mass * 1000000.f / r2};
        masses[i].displacement += (F / masses[i].mass) * d;
        
        // calculate actual displacement
        masses[i].displacement = masses[i].velocity     * tDelta
                               + masses[i].displacement * tHalfTDeltaSq;
    }
}

void Physics::testCollision(void) noexcept
{
    
}

void Physics::handleCollision(void) noexcept
{
    
}

void Physics::moveMasses(const GLfloat rTimeDelta) noexcept
{
    for (size_t i = 0; i < nMasses; ++i)
    {
        const vec3 displacement {masses[i].displacement};
        masses[i].position += displacement;
        masses[i].velocity = rTimeDelta * displacement;
    }
}
