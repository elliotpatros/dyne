//
//  OscInStream.cpp
//  dyne
//
//  Created by Elliot Patros on 4/3/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "OscInStream.h"

//==============================================================================
// static variables
//==============================================================================
OscInStream OscInStreamThread::oscIn
{
    OscInStream()
};

UdpListeningReceiveSocket OscInStreamThread::oscSocketIn
{
    UdpListeningReceiveSocket (IpEndpointName(IpEndpointName::ANY_ADDRESS, 9997),
                               &oscIn)
};

//==============================================================================
// constructor & destructor
//==============================================================================
OscInStreamThread::OscInStreamThread (void)
{
    stopThread();
}

OscInStreamThread::~OscInStreamThread (void)
{
    oscSocketIn.Break();
    stopThread();
}

void OscInStreamThread::startThread(void) noexcept
{
    pthread_create(&oscInThread, NULL, runOscStream, nullptr);
}

//==============================================================================
// osc input handling
//==============================================================================
float OscInStream::extractFloat(osc::ReceivedMessageArgumentStream args) noexcept
{
    float value;
    args >> value >> osc::EndMessage;
    return value;
}

void OscInStream::ProcessMessage (const osc::ReceivedMessage& m,
                                  const IpEndpointName& remoteEndpoint)
{
    try
    {
        const char* pattern {m.AddressPattern()};
        if (std::strcmp(pattern, "/gravity") == 0)
        {
            Physics::scaleGravity(extractFloat(m.ArgumentStream()));
        }
        else if (std::strcmp(pattern, "/timeStretch") == 0)
        {
            Physics::scaleTime(extractFloat(m.ArgumentStream()));
        }
        else if (std::strcmp(pattern, "/centerMass") == 0)
        {
            Physics::scaleCenterMass(extractFloat(m.ArgumentStream()));
        }
        else if (std::strcmp(pattern, "/pause") == 0)
        {
            Physics::pause(extractFloat(m.ArgumentStream()));
        }
        else if (std::strcmp(pattern, "/nMasses") == 0)
        {
            GravityBalls::setNBalls(extractFloat(m.ArgumentStream()));
        }
    }
    catch (osc::Exception& e)
    {
        IO::post("error while parsing message: ",
                 m.AddressPattern(),
                 ": ",
                 e.what());
    }
}

void* OscInStreamThread::runOscStream(void* arg)
{
    (void)arg;
    oscSocketIn.RunUntilSigInt();
    return NULL;
}
void OscInStreamThread::stopThread(void) noexcept
{
    pthread_cancel(oscInThread);
    pthread_join(oscInThread, NULL);
}
