#include "stdafx.h"
#include "client.h"


[!output CLIENT_CLASS_NAME]::[!output CLIENT_CLASS_NAME]( const char* key )
{
	clientKey = key;
}

[!output CLIENT_CLASS_NAME]::~[!output CLIENT_CLASS_NAME]()
{
	//
}

const char* [!output CLIENT_CLASS_NAME]::getKey()
{
	return clientKey.c_str();
}

PushFramework::SendResult [!output CLIENT_CLASS_NAME]::PushPacket( protobuf::Message* pMessage )
{
	OutgoingPacket* pPacket = reinterpret_cast<OutgoingPacket*> (pMessage);
	return LogicalConnection::PushPacket(pPacket);
}
