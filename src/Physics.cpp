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
const GLfloat Physics::clockHz (1000.f);
const GLfloat Physics::tDeltaConstant (hzToMs(clockHz) / 1000.f);
GLfloat Physics::tDelta (tDeltaConstant);
GLfloat Physics::tHalfDeltaSq (Physics::tDelta * Physics::tDelta * 0.5f);
GLfloat Physics::rTDelta (1.f / Physics::tDelta);

const GLfloat Physics::gravityConstant (6.67408f * powf(10.f, -5.f));
const GLfloat Physics::elasticity (1.f);
GLfloat Physics::gravity (gravityConstant);
const GLfloat Physics::centerMassConstant (10000.f);
GLfloat Physics::centerMass (centerMassConstant);

// time
bool Physics::readyToPlay (true);
pthread_mutex_t Physics::lock (PTHREAD_MUTEX_INITIALIZER);

// masses
size_t Physics::nMasses (0);
size_t Physics::nMassesMinusOne (0);
vector<MassyObject> Physics::masses {vector<MassyObject> ()};
GLfloat MassyObject::pos (45.f);

//==============================================================================
// constructor and destructor
//==============================================================================
Physics::Physics(void)
{
    pause(1.f);
    masses.reserve(DYNE_MAX_GBALLS);
    masses.clear();
//    masses.resize(DYNE_MAX_GBALLS);
}

Physics::~Physics(void) {}

//==============================================================================
// public functions
//==============================================================================
void Physics::setNMasses(const size_t n)
{
    masses.resize(n);
    nMasses = (n == 0) ? 0 : masses.size();
    nMassesMinusOne = (nMasses == 0) ? 0 : nMasses - 1;
//    nMasses = n;
//    nMassesMinusOne = nMasses - 1;
}

void Physics::setup(const size_t nMassesAtStart)
{
    setHz(clockHz);
    setNMasses(nMassesAtStart);
    
    pthread_mutex_init(&lock, NULL);
}

void Physics::scaleTime(const GLfloat scale) noexcept
{
    pthread_mutex_lock(&lock);
    tDelta = tDeltaConstant * scale;
    tHalfDeltaSq = tDelta * tDelta * 0.5f;
    rTDelta = 1.f / tDelta;
    pthread_mutex_unlock(&lock);
}

void Physics::scaleGravity(const GLfloat scale) noexcept
{
    pthread_mutex_lock(&lock);
    gravity = gravityConstant * scale;
    pthread_mutex_unlock(&lock);
}

void Physics::scaleCenterMass(const GLfloat scale) noexcept
{
    pthread_mutex_lock(&lock);
    centerMass = centerMassConstant * scale;
    pthread_mutex_unlock(&lock);
}

void Physics::pause(const GLfloat pauseIfZero) noexcept
{
    pthread_mutex_lock(&lock);
    readyToPlay = pauseIfZero != 0;
    pthread_mutex_unlock(&lock);
}

//==============================================================================
// threaded physics update
//==============================================================================
void Physics::timerCallback(void) noexcept
{
    if (readyToPlay)
    {
        // reset displacement and hit
        for (size_t i = 0; i < nMasses; ++i)
        {
            masses[i].hit = false;
            masses[i].displacement = vec3(0.f);
        }
        
        pthread_mutex_lock(&lock);
        accumulateDisplacement();
        collide();
        moveMasses();
        pthread_mutex_unlock(&lock);
    }
}

//==============================================================================
// physics helper functions
//==============================================================================
void Physics::accumulateDisplacement(void) noexcept
{
    for (size_t A = 0; A < nMassesMinusOne; ++A)
    {
        const GLfloat ATimesGravity (gravity * masses[A].mass);
        
        for (size_t B = A + 1; B < nMasses; ++B)
        {
            const vec3 AB (masses[B].position - masses[A].position);
            const GLfloat F (ATimesGravity * masses[B].mass
                          / (AB.x * AB.x + AB.y * AB.y + AB.z * AB.z));
            masses[A].displacement += (F / masses[A].mass) *  AB;
            masses[B].displacement += (F / masses[B].mass) * -AB;
        }
    }
    
    for (size_t i = 0; i < nMasses; ++i)
    {
        // make a gravitational center without size
        const vec3 d (-masses[i].position);
        const GLfloat F (gravity * masses[i].mass * centerMass
                      / tmax (d.x * d.x + d.y * d.y + d.z * d.z, 10.f));
        masses[i].displacement += (F / masses[i].mass) * d;
        
        // calculate actual displacement
        masses[i].displacement = masses[i].velocity     * tDelta
                               + masses[i].displacement * tHalfDeltaSq;
    }
}

void Physics::collide(void) noexcept
{
    for (size_t A = 0; A < nMassesMinusOne; ++A)
    {
        for (size_t B = A + 1; B < nMasses; ++B)
        {   // test for collision in this frame
            vec3 V (masses[A].displacement - masses[B].displacement);
            const vec3 P (masses[A].position - masses[B].position);
            const GLfloat radii (masses[A].radius + masses[B].radius);
            const GLfloat a ( 2.f * glm::dot(V, V));
            const GLfloat b (-2.f * glm::dot(P, V));
            const GLfloat c (glm::dot(P, P) - (radii * radii));
            const GLfloat discriminant (b * b - 2.f * a * c);
            
            // if discriminant is positive, the linear paths of A and B collide
            if (discriminant <= 0.f) {continue; }
            const GLfloat hitTime ((b - sqrtf(discriminant)) / a);
            
            // if hit time is between 0 and 1, A and B hit in this frame
            if (hitTime < 0.f || hitTime > 1.f)
            {
                continue;
            }
            else
            {
                masses[A].hitSinceLastDrawn =
                masses[A].hit =
                masses[B].hitSinceLastDrawn =
                masses[B].hit = true;
            }
            
            const GLfloat tCPA (b / a);
            const vec3 CPA (glm::abs((masses[A].position + tCPA * masses[A].displacement)
                                   - (masses[B].position + tCPA * masses[B].displacement)));
            
            // handle collision
            const vec3 Ahitpos (masses[A].position + masses[A].displacement * hitTime);
            const vec3 Bhitpos (masses[B].position + masses[B].displacement * hitTime);
            
            if (tmax(CPA.x, CPA.y, CPA.z) < dyne_epsilon)
            {   // collision is head on. only need to negate velocity
                masses[A].velocity *= -elasticity;
                masses[B].velocity *= -elasticity;
            }
            else
            {   // collision is not head on, get ready...
                // transform into B space
                vec3 Ap (Ahitpos - Bhitpos);
                vec3 Av (V);
                
                // rotate Av onto xy plane
                const GLfloat thetaZ (atanf(Ap.z / Ap.x));
                const GLfloat startY (atanf(Ap.y / sqrtf(Ap.x * Ap.x + Ap.z * Ap.z)));
                const GLfloat thetaY ((Ap.x > 0.f) ? startY : pi - startY);
                const mat3 rotateZ (glm::rotate(mat4(), thetaZ, vec3(0.f, 1.f,  0.f)));
                const mat3 rotateY (glm::rotate(mat4(), thetaY, vec3(0.f, 0.f, -1.f)));
                Av = rotateY * (rotateZ * Av);
                const mat3 rotateX (glm::rotate(mat4(), atanf(Av.z / Av.y), vec3(-1.f, 0.f, 0.f)));
                Av = rotateX * Av;
                
                // handle collision in 2D
                const GLfloat Avx ((masses[A].mass * Av.x - masses[B].mass * elasticity * Av.x)
                                 / (masses[A].mass + masses[B].mass));
                vec3 Bv (elasticity * Av.x + Avx, 0.f, 0.f);
                Av = vec3(Avx, Av.y, 0.f);
                
                // transform back into global space
                const mat3 rotateBack (glm::transpose(rotateZ)
                                    * (glm::transpose(rotateY)
                                    *  glm::transpose(rotateX)));
                Av = rotateBack * Av + masses[B].displacement;
                Bv = rotateBack * Bv + masses[B].displacement;
                
                // update velocity
                masses[A].velocity = Av * rTDelta;
                masses[B].velocity = Bv * rTDelta;
            }
            
            // update position
            const GLfloat timeAfterHit (tDelta * (1.f - hitTime));
            masses[A].position = Ahitpos + masses[A].velocity * timeAfterHit;
            masses[B].position = Bhitpos + masses[B].velocity * timeAfterHit;
            
            A = B;
            break;
        }
    }
}

void Physics::moveMasses() noexcept
{
    // move any unhit masses based on velocity and position
    for (size_t i = 0; i < nMasses; ++i)
    {
        if (masses[i].hit) {continue; }
        masses[i].position += masses[i].displacement;
        masses[i].velocity = masses[i].displacement * rTDelta;
    }
}
