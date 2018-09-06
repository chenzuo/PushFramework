#include "stdafx.h"
#include "TextSerializer.h"


TextSerializer::TextSerializer(void)
{
}


TextSerializer::~TextSerializer(void)
{
}

SerializeResult::Type TextSerializer::serializeMessage( OutgoingPacket& outgoingPacket, Buffer& buffer )
{
	TextMessage& text = (TextMessage&) outgoingPacket;

	if (buffer.getRemainingSize() < text.getSize())
		return SerializeResult::InsufficientBufferSpace;

	buffer.append(text.getContent(), text.getSize());

	return SerializeResult::Success;
}

DeserializeResult::Type TextSerializer::deserializeMessage( Buffer& contentBytes, IncomingPacket*& pMessage, int& nRoutingService )
{
	nRoutingService = 1;
	unsigned int size = contentBytes.getDataSize();

	pMessage = new TextMessage(contentBytes.getBuffer(), size);
	return DeserializeResult::Success;
}

void TextSerializer::disposeIncomingPacket( IncomingPacket* pPacket )
{
	TextMessage* text = (TextMessage*) pPacket;
	delete text;
}

void TextSerializer::disposeOutgoingPacket( OutgoingPacket* pPacket )
{
	TextMessage* text = (TextMessage*) pPacket;
	delete text;
}

unsigned int TextSerializer::getMaximumMessageSize()
{
	return (65536 + 100);
}

