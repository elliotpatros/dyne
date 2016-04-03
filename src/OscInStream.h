//
//  OscInStream.h
//  dyne
//
//  Created by Elliot Patros on 4/3/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__OscInStream__
#define __dyne__OscInStream__

#include "DyneBase.h"
#include "OSCBase.h"
#include "Maths.h"

#include <signal.h>

#include "GravityBalls.h"

class OscInStream : public osc::OscPacketListener
{
protected:
    virtual void ProcessMessage (const osc::ReceivedMessage& m,
                                 const IpEndpointName& remoteEndpoint);
    
    float extractFloat(osc::ReceivedMessageArgumentStream args) noexcept;
};

class OscInStreamThread
{
public:
    OscInStreamThread (void);
    ~OscInStreamThread (void);
    
    void startThread(void) noexcept;
    void stopThread(void) noexcept;
    
    
private:
    static OscInStream oscIn;
    static UdpListeningReceiveSocket oscSocketIn;
    
    pthread_t oscInThread;
    static void* runOscStream(void* arg);
};

#endif
