
#include "StdAfx.h"
#include "OutgoingXMLPacket.h"



OutgoingXMLPacket::OutgoingXMLPacket( unsigned int uCommandID )
{
    this->uCommandID = uCommandID;
    xRoot = XMLNode::createXMLTopNode("r");
    //
    bEncoded = false;
    pEncodedString = NULL;
    uBufferSize = 0;
}

OutgoingXMLPacket::~OutgoingXMLPacket()
{
    freeXMLString(pEncodedString);
}

void OutgoingXMLPacket::setArgumentAsText(const char* argName, const char* sArgVal )
{
    xRoot.addChild(argName).addAttribute("v", sArgVal);
}

void OutgoingXMLPacket::setArgumentAsInt( const char* argName, int iArgVal )
{
    std::stringstream ss;
    ss << iArgVal;
    setArgumentAsText(argName, ss.str().c_str());
}
void OutgoingXMLPacket::setArgumentAsDouble( const char* argName, double val )
{
    std::stringstream ss;
    ss << val;
    setArgumentAsText(argName, ss.str().c_str());
}
void OutgoingXMLPacket::setArgumentAsBool( const char* argName, bool bArgVal )
{
    setArgumentAsText(argName, bArgVal ? "1" : "0");
}

bool OutgoingXMLPacket::Encode()
{
    if(bEncoded)
        return true;
    if(!ConstructXML())
        return false;
    int nSize;
    pEncodedString = xRoot.createXMLString(0, &nSize);
    uBufferSize = nSize * sizeof(char);
    bEncoded = true;
    return true;
}

unsigned int OutgoingXMLPacket::getBufferLen()
{
    return uBufferSize;
}

char* OutgoingXMLPacket::getBuffer()
{
    return pEncodedString;
}

unsigned int OutgoingXMLPacket::getRequestId()
{
    return uCommandID;
}

XMLNode OutgoingXMLPacket::getOutputXML()
{
    return xRoot;
}
