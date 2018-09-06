#include "StdAfx.h"
#include "TestClient.h"

CTestClient::CTestClient(const char* _pseudo)
{
    pseudo = _pseudo;
}

CTestClient::~CTestClient(void)
{
}

const char* CTestClient::getKey()
{
    return pseudo.c_str();
}

PushFramework::SendResult CTestClient::PushPacket( protobuf::Message* pMessage )
{
    OutgoingPacket* pPacket = reinterpret_cast<OutgoingPacket*> (pMessage);
    return LogicalConnection::PushPacket(pPacket);
}
