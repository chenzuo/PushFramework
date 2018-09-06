#ifndef OutgoingXMLPacket__INCLUDED
#define OutgoingXMLPacket__INCLUDED

#pragma once
#include "Symbols.h"
#include "xmlParser.h"


class XMLPROTOCOL_API OutgoingXMLPacket : public PushFramework::OutgoingPacket
{
public:
    OutgoingXMLPacket(unsigned int uCommandID);
    virtual ~OutgoingXMLPacket();
    void setArgumentAsText(const char* argName, const char* sArgVal);
    void setArgumentAsInt(const char* argName, int iArgVal);
    void setArgumentAsDouble(const char* argName, double val);
    void setArgumentAsBool(const char* argName, bool bArgVal);
    virtual bool Encode();
    virtual unsigned int getBufferLen();
    virtual char* getBuffer();
    unsigned int getRequestId();
    virtual bool ConstructXML() = 0;
    XMLNode getOutputXML();
    virtual void* CreateInstance() = 0;
private:
    unsigned int uCommandID;
    XMLNode xRoot;
    bool bEncoded;
    char* pEncodedString;
    unsigned int uBufferSize;
};
#endif // OutgoingXMLPacket__INCLUDED
