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
protected:
    PosixThread(void);
    ~PosixThread(void);
    
    bool runThread(void) noexcept;
    void joinThread(void) noexcept;
    void cancelThread(void) noexcept;
    virtual void threadedFunction(void* arg) = 0;
    static bool shouldQuit(PosixThread* t) noexcept;
    
    pthread_t thread;
    pthread_mutex_t* quitFlag;
    
    
private:
    static void* func(void* This);
};

#endif
