#pragma once

namespace testsuitemessages
{

class ProtobufProtocol: public Protocol {
public:
    ProtobufProtocol(void);
    ~ProtobufProtocol();	
    virtual void disposeOutgoingPacket(OutgoingPacket* pPacket);
    virtual void disposeIncomingPacket(IncomingPacket* pPacket);
protected:
    virtual void registerMessage(int type, const protobuf::Message* message);
private:
	typedef map<string, int> TypeNameToIdMapT;
	typedef map<int, const protobuf::Message*> IdToTypeMapT;
    TypeNameToIdMapT typeNameToIdMap;
    IdToTypeMapT idToTypeMap;
protected:
    virtual int encodeOutgoingPacket(OutgoingPacket& packet);
    virtual int frameOutgoingPacket(OutgoingPacket& packet, DataBuffer& buffer, unsigned int& nWrittenBytes);
    //
    virtual int tryDeframeIncomingPacket(DataBuffer& buffer, IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext);
    virtual int decodeIncomingPacket(IncomingPacket* pPacket, int& serviceId);
};

}
