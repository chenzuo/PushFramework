#pragma once

class LicenseProtocol : public Protocol
{
public:
    LicenseProtocol(void);
    ~LicenseProtocol(void);

    virtual void disposeOutgoingPacket(OutgoingPacket* pPacket);
    virtual void disposeIncomingPacket(IncomingPacket* pPacket);

    virtual int encodeOutgoingPacket(OutgoingPacket& packet);
    virtual int frameOutgoingPacket(OutgoingPacket& packet, DataBuffer& buffer, unsigned int& nWrittenBytes);

    virtual int tryDeframeIncomingPacket(DataBuffer& buffer, IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext);
    virtual int decodeIncomingPacket(IncomingPacket* pPacket, int& serviceId);

};
