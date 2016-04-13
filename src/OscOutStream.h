//
//  OscOutStream.h
//  dyne
//
//  Created by Elliot Patros on 4/5/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#ifndef __dyne__OscOutStream__
#define __dyne__OscOutStream__

#include "DyneBase.h"
#include "OSCBase.h"
#include "Physics.h"

class OscOutStream
{
public:
    OscOutStream(void);
    
    void sendPhysicsInfo(vector<MassyObject>* masses) noexcept;
    void sendBang(const char* tag) noexcept;
    
private:
    static const char* address;
    int port;
    static const int bufferSize;
    static const char* positionTag;
    static string numberTag[DYNE_MAX_GBALLS];
    
    UdpTransmitSocket transmitSocket;
};

#endif
