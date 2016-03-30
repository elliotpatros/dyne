//
//  PosixThread.cpp
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "PosixThread.h"

PosixThread::PosixThread(void)
{
    thread = 0;
    shouldQuit = true;
}

PosixThread::~PosixThread(void)
{
    cancelThread();
}

/** returns true if the thread successfully starts */
bool PosixThread::runThread(void) noexcept
{
    if (   (thread == 0)         // thread is unused
        && (shouldQuit == true)) // mutex is not busy
    {
        shouldQuit = false;
        return (pthread_create(&thread, NULL, func, this) == 0);
    }
    
    return false;
}

void PosixThread::joinThread(void) noexcept
{
    if (thread != 0)
    {
        (void)pthread_join(thread, NULL);
        thread = 0;
    }
}

void PosixThread::cancelThread(void) noexcept
{
    shouldQuit = true;
    joinThread();
}

void* PosixThread::func(void* This)
{
    ((PosixThread *)This)->threadedFunction(This);
    
    return NULL;
}
