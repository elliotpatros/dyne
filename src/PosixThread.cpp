//
//  PosixThread.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "PosixThread.h"

PosixThread::PosixThread(void)
: quitFlag((pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)))
{
    thread = 0;
}

PosixThread::~PosixThread(void)
{
    if (quitFlag != 0) {free(quitFlag); }
    
    quitFlag = 0;
}

/** returns true if the thread successfully starts */
bool PosixThread::runThread(void) noexcept
{
    if (   (thread == 0)        // thread is unused
        && (quitFlag != 0)      // mutex is valid
        && (shouldQuit(this)))  // mutex is not busy
    {
        pthread_mutex_init(quitFlag, NULL);
        pthread_mutex_lock(quitFlag);
        return (pthread_create(&thread, NULL, func, this) == 0);
    }
    
    return false;
}

void PosixThread::joinThread(void) noexcept
{
    if (thread != 0)
    {
        (void)pthread_join(thread, NULL);
    }
}

void PosixThread::cancelThread(void) noexcept
{
    if (thread != 0)
    {
        pthread_mutex_unlock(quitFlag);
        (void)pthread_join(thread, NULL);
    }
}

void* PosixThread::func(void* This)
{
    ((PosixThread *)This)->threadedFunction(This);
    
    return NULL;
}

bool PosixThread::shouldQuit(PosixThread* t) noexcept
{
    return pthread_mutex_trylock(t->quitFlag) != EBUSY;
}
