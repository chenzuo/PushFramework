#include "StdAfx.h"
#include "XMLProtocolImpl.h"

#include "XMLRequest.h"
#include "XMLResponse.h"

#define SignatureStart 16018
#define SignatureEnd 16108



XMLProtocolImpl::XMLProtocolImpl(void)
{

}

XMLProtocolImpl::~XMLProtocolImpl(void)
{

}



int XMLProtocolImpl::encodeOutgoingPacket( PushFramework::OutgoingPacket& packet )
{
    OutgoingXMLPacket& xmlPacket = (OutgoingXMLPacket&) packet;

    return xmlPacket.Encode() ? PushFramework::Protocol::Success : PushFramework::Protocol::eEncodingFailure;
}


int XMLProtocolImpl::frameOutgoingPacket( PushFramework::OutgoingPacket& packet, PushFramework::DataBuffer& buffer, unsigned int& nWrittenBytes )
{
    OutgoingXMLPacket& xmlPacket = (OutgoingXMLPacket&) packet;

    nWrittenBytes = 6 + xmlPacket.getBufferLen() + 2;

    if(nWrittenBytes > buffer.getRemainingSize())
        return PushFramework::Protocol::eInsufficientBuffer;

    unsigned int sStart = SignatureStart;
    unsigned int packetLen = nWrittenBytes;
    unsigned int commandID = xmlPacket.getRequestId();
    unsigned int sEnd = SignatureEnd;

    buffer.append((char*)&sStart, 2);
    buffer.append((char*)&packetLen, 2);
    buffer.append((char*)&commandID, 2);

    buffer.append(xmlPacket.getBuffer(), xmlPacket.getBufferLen());

    buffer.append((char*)&sEnd, 2);

    return PushFramework::Protocol::Success;
}

int XMLProtocolImpl::tryDeframeIncomingPacket( PushFramework::DataBuffer& buffer, PushFramework::IncomingPacket*& pPacket, int& serviceId, unsigned int& nExtractedBytes )
{
    if(buffer.getDataSize() <= 8)
        return PushFramework::Protocol::eIncompletePacket;

    char* pBuffer = buffer.getBuffer();

    unsigned int sStart = 0;
    unsigned int packetLen = 0;
    serviceId = 0;
    unsigned int sEnd = 0;

    for (int i=0; i<2; i++)
    {
        *((char*)(&sStart)+i)=pBuffer[i];
        *((char*)(&packetLen)+i)=pBuffer[i+2];
        *((char*)(&serviceId)+i)=pBuffer[i+4];
    }

    if (sStart!=SignatureStart)
        return PushFramework::Protocol::eCorruptPacket;

    if (packetLen > buffer.getDataSize())
        return PushFramework::Protocol::eIncompletePacket;

    for (int i=0; i<2; i++)
        *((char*)(&sEnd)+i)=pBuffer[packetLen-2+i];

    if(sEnd!=SignatureEnd)
        return PushFramework::Protocol::eCorruptPacket;

    char* pData = pBuffer + 6;
    unsigned int dataSize = packetLen - 8;

    nExtractedBytes = packetLen;

    IncomingXMLPacket* pIncomingXMLPacket = (IncomingXMLPacket*)createIncomingPacket(serviceId);
    if(pIncomingXMLPacket==NULL)
        return PushFramework::Protocol::eUndefinedFailure;

    if(!pIncomingXMLPacket->Decode(pData, dataSize))
    {
        disposeIncomingPacket(pIncomingXMLPacket);
        return PushFramework::Protocol::eDecodingFailure;
    }

    pPacket = (PushFramework::IncomingPacket*) pIncomingXMLPacket;
    return PushFramework::Protocol::Success;
}



void XMLProtocolImpl::disposeIncomingPacket( PushFramework::IncomingPacket* pPacket )
{
    delete pPacket;
}


PushFramework::IncomingPacket* XMLProtocolImpl::createIncomingPacket( unsigned int serviceId )
{
    inFactoryMapT::iterator it = inFactoryMap.find(serviceId);
    if(it==inFactoryMap.end())
        return NULL;


    IncomingPacketTypeInfo* pInfo = it->second;

    return (PushFramework::IncomingPacket*) pInfo->pTemplate->CreateInstance();
}

void XMLProtocolImpl::disposeOutgoingPacket( PushFramework::OutgoingPacket* pPacket )
{
    delete pPacket;
}
PushFramework::OutgoingPacket* XMLProtocolImpl::createOutgoingPacket( unsigned int requestId )
{
    outFactoryMapT::iterator it = outFactoryMap.find(requestId);
    if(it==outFactoryMap.end())
        return NULL;


    OutgoingPacketTypeInfo* pInfo = it->second;

    return (PushFramework::OutgoingPacket*) pInfo->pTemplate->CreateInstance();
}

void XMLProtocolImpl::registerIncomingPacketTemplate( unsigned int serviceId, PushFramework::IncomingPacket* pTemplate, unsigned int nMaxPool )
{
    IncomingPacketTypeInfo* pInfo = new IncomingPacketTypeInfo;
    pInfo->pTemplate = (IncomingXMLPacket*) pTemplate;
    inFactoryMap[serviceId] = pInfo;
}

void XMLProtocolImpl::registerOutgoingPacketTemplate( unsigned int requestId, PushFramework::OutgoingPacket* pTemplate, unsigned int nMaxPool )
{
    OutgoingPacketTypeInfo* pInfo = new OutgoingPacketTypeInfo;
    pInfo->pTemplate = (OutgoingXMLPacket*)pTemplate;
    outFactoryMap[requestId] = pInfo;
}

int XMLProtocolImpl::decodeIncomingPacket( PushFramework::IncomingPacket* pPacket, int& serviceId )
{
    return PushFramework::Protocol::Success;
}


