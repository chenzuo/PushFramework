#include "stdafx.h"
#include "protocol.h"

#define SignatureStart 16018
#define SignatureEnd 16108

ProtobufProtocol::ProtobufProtocol()
{
	//
}

ProtobufProtocol::~ProtobufProtocol()
{
	//
}

void ProtobufProtocol::registerMessage( const protobuf::Message* message )
{
	int type = hash(message->GetTypeName());
	idToTypeMap[type] = message;
}

unsigned short ProtobufProtocol::hash( const string& s )
{
	unsigned short h = 0;
	for(string::const_iterator it=s.begin(); it!=s.end(); ++it) {
		h = (*it) + (h << 6) + (h << 16) - h;
	}
	return h;
}

int ProtobufProtocol::encodeOutgoingPacket( OutgoingPacket& packet )
{
	return Protocol::Success;
}

int ProtobufProtocol::frameOutgoingPacket( OutgoingPacket& packet, DataBuffer& buffer, unsigned int& nWrittenBytes )
{
	protobuf::Message& gMessage = reinterpret_cast<protobuf::Message&> (packet);

	unsigned short type = hash(gMessage.GetTypeName());


	if (buffer.getRemainingSize() < 8)
		return Protocol::eInsufficientBuffer;

	//Try write the message :
	string strEncoded = gMessage.SerializePartialAsString();
	unsigned int nTotalPacketSize = 6 + strEncoded.size() + 2;

	if (nTotalPacketSize > buffer.getRemainingSize())
	{
		return Protocol::eInsufficientBuffer;
	}

	//Write Header :
	unsigned int sStart = SignatureStart;
	unsigned int packetLen = nTotalPacketSize;
	unsigned int commandID = type;
	buffer.append((char*) &sStart, 2);
	buffer.append((char*)&packetLen, 2);
	buffer.append((char*)&commandID, 2);

	buffer.append((char*) strEncoded.c_str(), strEncoded.size());

	unsigned int sEnd = SignatureEnd;
	buffer.append((char*)&sEnd, 2);

	nWrittenBytes = packetLen;
	return Protocol::Success;
}

int ProtobufProtocol::decodeIncomingPacket( IncomingPacket* pPacket, int& serviceId )
{
	return Success;
}

int ProtobufProtocol::tryDeframeIncomingPacket( DataBuffer& buffer, IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes, ConnectionContext* pContext )
{
	if( buffer.getDataSize() < 8 )
		return Protocol::eIncompletePacket;

	char* pBuffer = buffer.getBuffer();

	unsigned int sStart = 0;
	unsigned int packetLen = 0;
	serviceId = 0;
	unsigned int sEnd = 0;

	for (int i=0; i<2; i++)
	{
		*((BYTE*)(&sStart)+i)=pBuffer[i];
		*((BYTE*)(&packetLen)+i)=pBuffer[i+2];
		*((BYTE*)(&serviceId)+i)=pBuffer[i+4];
	}

	if (sStart!=SignatureStart)
		return Protocol::eCorruptPacket;

	if ( packetLen > buffer.getDataSize() )
		return Protocol::eIncompletePacket;

	for (int i=0; i<2; i++)
		*((BYTE*)(&sEnd)+i)=pBuffer[ packetLen-2+i ];

	if( sEnd != SignatureEnd )
		return Protocol::eCorruptPacket;

	nExtractedBytes = packetLen;

	map<unsigned short, const protobuf::Message*>::iterator it = idToTypeMap.find((unsigned short)serviceId);
	if (it == idToTypeMap.end())
		return Protocol::eUndefinedFailure; 

	protobuf::Message * pMessage = it->second->New();
	if (!pMessage->ParsePartialFromArray(pBuffer + 6, packetLen - 8))
	{
		delete pMessage;
		return Protocol::eDecodingFailure;
	}
	pPacket = reinterpret_cast<IncomingPacket*> (pMessage);
	return Protocol::Success;
}

void ProtobufProtocol::disposeIncomingPacket( IncomingPacket* pPacket )
{
	protobuf::Message* pMessage = reinterpret_cast<protobuf::Message*> (pPacket);
	delete pMessage;
}

void ProtobufProtocol::disposeOutgoingPacket( OutgoingPacket* pPacket )
{
	protobuf::Message* pMessage = reinterpret_cast<protobuf::Message*> (pPacket);
	delete pMessage;
}
