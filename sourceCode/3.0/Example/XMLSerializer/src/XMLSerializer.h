#pragma once;
#include "Symbols.h"


class XMLMessage;

// This class is exported from the XMLSerializer.dll
class XMLSERIALIZER_API XMLSerializer : public MessageFactory
{
public:
	XMLSerializer(void);
	~XMLSerializer();
	

protected:
	virtual SerializeResult::Type serializeMessage(OutgoingPacket& outgoingPacket, Buffer& buffer);
	virtual DeserializeResult::Type deserializeMessage(Buffer& contentBytes, IncomingPacket*& pMessage, int& nRoutingService);
	virtual bool preSerializeMessage(OutgoingPacket& outgoingPacket);
	virtual void disposeIncomingPacket(IncomingPacket* pPacket);
	virtual void disposeOutgoingPacket(OutgoingPacket* pPacket);

};


