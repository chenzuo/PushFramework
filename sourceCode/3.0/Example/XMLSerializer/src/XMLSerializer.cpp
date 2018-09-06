// XMLSerializer.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "XMLSerializer.h"
#include "XMLMessage.h"

// This is the constructor of a class that has been exported.
// see XMLSerializer.h for the class definition
XMLSerializer::XMLSerializer()
{
	return;
}

XMLSerializer::~XMLSerializer()
{
	//
}

void XMLSerializer::disposeIncomingPacket( IncomingPacket* pPacket )
{
	XMLMessage* pXMLMessage = (XMLMessage*) pPacket;
	delete pXMLMessage;
}

void XMLSerializer::disposeOutgoingPacket( OutgoingPacket* pPacket )
{
	XMLMessage* pXMLMessage = (XMLMessage*) pPacket;
	delete pXMLMessage;
}

SerializeResult::Type XMLSerializer::serializeMessage( OutgoingPacket& outgoingPacket, Buffer& buffer )
{
	XMLMessage& message = (XMLMessage&) outgoingPacket;

	message.Encode();

	if (buffer.getCapacity() < (message.getData().length() + 1))
	{
		return SerializeResult::InsufficientBufferSpace; //TODO. Verify this.
	}

	buffer.append(message.getData().c_str(), message.getData().length());
	
	char endChar = 0;
	buffer.append(&endChar, 1);
	
	return SerializeResult::Success;
}

DeserializeResult::Type XMLSerializer::deserializeMessage( Buffer& contentBytes, IncomingPacket*& pMessage, int& nRoutingService )
{
	if(contentBytes.getDataSize() == 0)
	{
		return DeserializeResult::DiscardContent;
	}

	char endChar = contentBytes.getAt(contentBytes.getDataSize() - 1);

	if (endChar != 0)
	{
		return DeserializeResult::Failure;
	}
 
	XMLMessage* message = XMLMessage::CreateFromBuffer(contentBytes.getBuffer());

	if (!message)
	{
		return DeserializeResult::Failure;
	}

	pMessage = (IncomingPacket*) message;
	nRoutingService = message->getTypeId();

	return DeserializeResult::Success;
}

bool XMLSerializer::preSerializeMessage( OutgoingPacket& outgoingPacket )
{
	XMLMessage& message = (XMLMessage&) outgoingPacket;
	message.Encode();
	return true;
}
