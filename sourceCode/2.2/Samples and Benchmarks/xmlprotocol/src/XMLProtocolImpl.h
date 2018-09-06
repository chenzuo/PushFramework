#ifndef XMLProtocolImpl__INCLUDED
#define XMLProtocolImpl__INCLUDED

#pragma once

class IncomingXMLPacket;
class OutgoingXMLPacket;

struct IncomingPacketTypeInfo
{
    IncomingXMLPacket* pTemplate;
};
struct OutgoingPacketTypeInfo
{
    OutgoingXMLPacket* pTemplate;
};

class XMLProtocolImpl
{
public:
    XMLProtocolImpl(void);
    ~XMLProtocolImpl(void);


    void registerIncomingPacketTemplate(unsigned int serviceId, PushFramework::IncomingPacket* pTemplate, unsigned int nMaxPool );
    void registerOutgoingPacketTemplate(unsigned int requestId, PushFramework::OutgoingPacket* pTemplate, unsigned int nMaxPool );

    PushFramework::OutgoingPacket* createOutgoingPacket(unsigned int requestId);
    PushFramework::IncomingPacket* createIncomingPacket(unsigned int serviceId);

    void disposeOutgoingPacket(PushFramework::OutgoingPacket* pPacket);
    void disposeIncomingPacket(PushFramework::IncomingPacket* pPacket);


    virtual int encodeOutgoingPacket(PushFramework::OutgoingPacket& packet);
    virtual int frameOutgoingPacket(PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes);
    virtual int tryDeframeIncomingPacket(PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes);
    virtual int decodeIncomingPacket(PushFramework::IncomingPacket* pPacket, int& serviceId);

private:


    typedef std::map<unsigned int, IncomingPacketTypeInfo*> inFactoryMapT;
    inFactoryMapT inFactoryMap;

    typedef std::map<unsigned int, OutgoingPacketTypeInfo*> outFactoryMapT;
    outFactoryMapT outFactoryMap;

};
#endif // XMLProtocolImpl__INCLUDED
