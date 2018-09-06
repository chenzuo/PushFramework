#ifndef XMLProtocol__INCLUDED
#define XMLProtocol__INCLUDED

#pragma once

#include "Symbols.h"

class XMLProtocolImpl;

class XMLRequest;
class XMLResponse;


class XMLPROTOCOL_API XMLProtocol : public PushFramework::Protocol
{
public:
    XMLProtocol();
    ~XMLProtocol();


    virtual void disposeOutgoingPacket(PushFramework::OutgoingPacket* pPacket);
    virtual void disposeIncomingPacket(PushFramework::IncomingPacket* pPacket);

    void registerIncomingPacketTemplate(unsigned int serviceId, PushFramework::IncomingPacket* pTemplate, unsigned int nMaxPool );
    void registerOutgoingPacketTemplate(unsigned int requestId, PushFramework::OutgoingPacket* pTemplate, unsigned int nMaxPool );

    PushFramework::OutgoingPacket* createOutgoingPacket(unsigned int requestId);
    PushFramework::IncomingPacket* createIncomingPacket(unsigned int serviceId);

    virtual int encodeOutgoingPacket(PushFramework::OutgoingPacket& packet);
    virtual int frameOutgoingPacket(PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes);

    virtual int tryDeframeIncomingPacket(PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, PushFramework::ConnectionContext* pContext);
    virtual int decodeIncomingPacket(PushFramework::IncomingPacket* pPacket, int& serviceId);


private:
    XMLProtocolImpl* pImpl;
};
#endif // XMLProtocol__INCLUDED
