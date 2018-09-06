
#include "Symbols.h"

#include "TextMessage.h"

class TEXTSERIALIZER_API TextSerializer : public MessageFactory
{
public:
	TextSerializer(void);
	~TextSerializer(void);

	virtual SerializeResult::Type serializeMessage( OutgoingPacket& outgoingPacket, Buffer& buffer );

	virtual DeserializeResult::Type deserializeMessage( Buffer& contentBytes, IncomingPacket*& pMessage, int& nRoutingService );

	virtual void disposeIncomingPacket( IncomingPacket* pPacket );

	virtual void disposeOutgoingPacket( OutgoingPacket* pPacket );

	virtual unsigned int getMaximumMessageSize();

};