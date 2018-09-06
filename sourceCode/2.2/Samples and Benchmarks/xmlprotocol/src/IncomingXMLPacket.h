#ifndef IncomingXMLPacket__INCLUDED
#define IncomingXMLPacket__INCLUDED


#pragma once
#include "Symbols.h"
#include "xmlParser.h"

class XMLPROTOCOL_API IncomingXMLPacket : public PushFramework::IncomingPacket
{
public:
    IncomingXMLPacket();
    virtual ~IncomingXMLPacket(void);

    virtual bool Decode(char* pBuffer, unsigned int uBufferSize);
    const char* getArgumentAsText(const char* argName, bool& updateSuccess);
    int getArgumentAsInt(const char* argName, bool& updateSuccess);
    double getArgumentAsDouble(const char* argName, bool& updateSuccess);
    bool getArgumentAsBool(const char* argName, bool& updateSuccess);
    virtual bool FragmentXML() = 0;
    virtual void* CreateInstance() = 0;
    XMLNode getInputXML();
private:
    char* pString;
    unsigned int uBufferSize;
    //
    XMLNode xRoot;
};
#endif // IncomingXMLPacket__INCLUDED
