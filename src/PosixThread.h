//
//  PosixThread.h
//  dyne
//
//  Created by Elliot Patros on 3/18/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__PosixThread__
#define __dyne__PosixThread__

#include "DyneBase.h"

class PosixThread
{
public:
    typedef struct
    {
        PosixThread* This;
        void* arg;
    } PThread_Arg;
    
    
protected:
    PosixThread(void);
    
    bool runPThread(void);
    void joinPThread(void);
    
    /** Actual thread */
    virtual void threadedFunction(void* arg) = 0;
    static bool shouldQuit(PosixThread* t) noexcept;
    
    
private:
    pthread_t thread;
    pthread_mutex_t quitFlag;
    
    static void* func(void* This);
};

#endif
