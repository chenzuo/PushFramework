#include "StdAfx.h"
#include "XMLProtocol.h"

#include "XMLProtocolImpl.h"

XMLProtocol::XMLProtocol()
{
    pImpl = new XMLProtocolImpl();
}

XMLProtocol::~XMLProtocol()
{
    delete pImpl;
}


void XMLProtocol::disposeOutgoingPacket( PushFramework::OutgoingPacket* pPacket )
{
    return pImpl->disposeOutgoingPacket(pPacket);
}

void XMLProtocol::disposeIncomingPacket( PushFramework::IncomingPacket* pPacket )
{
    return pImpl->disposeIncomingPacket(pPacket);
}

void XMLProtocol::registerIncomingPacketTemplate( unsigned int serviceId, PushFramework::IncomingPacket* pTemplate, unsigned int nMaxPool )
{
    pImpl->registerIncomingPacketTemplate(serviceId, pTemplate, nMaxPool);
}

void XMLProtocol::registerOutgoingPacketTemplate( unsigned int requestId, PushFramework::OutgoingPacket* pTemplate, unsigned int nMaxPool )
{
    pImpl->registerOutgoingPacketTemplate(requestId, pTemplate, nMaxPool);
}

PushFramework::OutgoingPacket* XMLProtocol::createOutgoingPacket( unsigned int requestId )
{
    return pImpl->createOutgoingPacket(requestId);
}

PushFramework::IncomingPacket* XMLProtocol::createIncomingPacket( unsigned int serviceId )
{
    return pImpl->createIncomingPacket(serviceId);
}

int XMLProtocol::encodeOutgoingPacket( PushFramework::OutgoingPacket& packet )
{
    return pImpl->encodeOutgoingPacket(packet);
}

int XMLProtocol::frameOutgoingPacket( PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes )
{
    return pImpl->frameOutgoingPacket(packet, buffer, nWrittenBytes);
}

int XMLProtocol::tryDeframeIncomingPacket( PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, PushFramework::ConnectionContext* pContext )
{
    return pImpl->tryDeframeIncomingPacket(buffer, pPacket, serviceId, nExtractedBytes);
}

int XMLProtocol::decodeIncomingPacket( PushFramework::IncomingPacket* pPacket, int& serviceId )
{
    return pImpl->decodeIncomingPacket(pPacket, serviceId);
}

