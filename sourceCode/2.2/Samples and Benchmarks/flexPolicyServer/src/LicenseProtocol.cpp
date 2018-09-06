#include "StdAfx.h"
#include "LicenseProtocol.h"

#include "PolicyRequest.h"
#include "PolicyResponse.h"

LicenseProtocol::LicenseProtocol(void)
{
}

LicenseProtocol::~LicenseProtocol(void)
{
}

int LicenseProtocol::tryDeframeIncomingPacket( DataBuffer& buffer, IncomingPacket*& lpMessage, int& serviceId, unsigned int& uExtractedBytes, ConnectionContext* pContext )
{
    serviceId = 1;
    for (unsigned int i = 0; i<buffer.getDataSize(); i++)
    {
        char ch = buffer.getAt(i);
        if (ch=='\0')
        {
            //It is ok
            PolicyRequest* pRequest = new PolicyRequest();
            if (!pRequest->Decode(buffer.getBuffer(), i))
            {
                delete pRequest;
                return Protocol::eDecodingFailure;
            }
            lpMessage = (IncomingPacket*) pRequest;
            uExtractedBytes = i+1;
            return Protocol::Success;
        }
    }
    return Protocol::eIncompletePacket;
}

void LicenseProtocol::disposeOutgoingPacket( OutgoingPacket* pPacket )
{
    delete pPacket;
}

void LicenseProtocol::disposeIncomingPacket( IncomingPacket* pPacket )
{
    delete pPacket;
}


int LicenseProtocol::encodeOutgoingPacket( OutgoingPacket& packet )
{
    return Protocol::Success;
}

int LicenseProtocol::frameOutgoingPacket( OutgoingPacket& packet, DataBuffer& buffer, unsigned int& nWrittenBytes )
{
    PolicyResponse& response = (PolicyResponse&) packet;
    nWrittenBytes = response.getBufferLen() + 1;

    if(nWrittenBytes > buffer.getRemainingSize())
        return Protocol::eInsufficientBuffer;

    buffer.append(response.getBuffer(), response.getBufferLen());

    char endChar = 0;

    buffer.append(&endChar, 1);

    return Protocol::Success;

}

int LicenseProtocol::decodeIncomingPacket( IncomingPacket* pPacket, int& serviceId )
{
    return Protocol::Success;
}

