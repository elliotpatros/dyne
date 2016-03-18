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
//    cout << "thread = " << thread << endl;
}

/** returns true if the thread successfully starts */
bool PosixThread::runPThread(void)
{
    pthread_mutex_init(&quitFlag, NULL);
    pthread_mutex_lock(&quitFlag);
    return (pthread_create(&thread, NULL, func, this) == 0);
}

void PosixThread::joinPThread(void)
{
    if (thread != 0)
    {
        pthread_mutex_unlock(&quitFlag);
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
    return pthread_mutex_trylock(&t->quitFlag) != EBUSY;
}
