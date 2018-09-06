#pragma once

class ProtobufProtocol : public Protocol
{
public:
	ProtobufProtocol();
	~ProtobufProtocol();

	void registerMessage(const protobuf::Message* message);
	static unsigned short hash(const string& s);

protected:
	virtual int encodeOutgoingPacket(OutgoingPacket& packet);
	virtual int frameOutgoingPacket(OutgoingPacket& packet, DataBuffer& buffer, unsigned int& nWrittenBytes);
	//
	virtual int tryDeframeIncomingPacket(DataBuffer& buffer, IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext);
	virtual int decodeIncomingPacket(IncomingPacket* pPacket, int& serviceId);

	virtual void disposeIncomingPacket(IncomingPacket* pPacket);
	virtual void disposeOutgoingPacket(OutgoingPacket* pPacket);
private:
	typedef map<unsigned short, const protobuf::Message*> IdToTypeMapT;
	IdToTypeMapT idToTypeMap;
};