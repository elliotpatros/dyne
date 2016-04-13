//
//  OscOutStream.cpp
//  dyne
//
//  Created by Elliot Patros on 4/5/16.
//  Copyright (c) 2016 Elliot Patros. All rights reserved.
//

#include "OscOutStream.h"

const char* OscOutStream::address ("127.0.0.1");
const int OscOutStream::bufferSize (4096);
const char* OscOutStream::positionTag ("/pos");
string OscOutStream::numberTag[DYNE_MAX_GBALLS] {string()};

OscOutStream::OscOutStream(void) :
port (9998),
transmitSocket (IpEndpointName(address, port))
{
    for (size_t i = 0; i < DYNE_MAX_GBALLS; ++i)
    {
        numberTag[i] = std::to_string(i);
    }
}

void OscOutStream::sendPhysicsInfo(vector<MassyObject>* masses) noexcept
{
    char buffer[bufferSize];
    osc::OutboundPacketStream packet (buffer, bufferSize);
    packet << osc::BeginBundleImmediate;
    
    const size_t nMasses (masses->size());
    for (size_t m = 0; m < nMasses; ++m)
    {
        const vec3 pos (masses->at(m).position);
        
        packet << osc::BeginMessage((positionTag + numberTag[m]).c_str())
        << pos.x << pos.y << pos.z
        << osc::EndMessage;
    }
    
    packet << osc::EndBundle;
    transmitSocket.Send(packet.Data(), packet.Size());
}

void OscOutStream::sendBang(const char* tag) noexcept
{
    char buffer[bufferSize];
    osc::OutboundPacketStream packet (buffer, bufferSize);
    
    packet << osc::BeginBundleImmediate
    << osc::BeginMessage(tag) << osc::EndMessage
    << osc::EndBundle;
    
    transmitSocket.Send(packet.Data(), packet.Size());
}
