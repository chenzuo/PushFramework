#include "StdAfx.h"
#include "IncomingXMLPacket.h"


IncomingXMLPacket::IncomingXMLPacket(  )
{
    xRoot = XMLNode::emptyNode();
    //
    uBufferSize = 0;
    pString = NULL;
}

IncomingXMLPacket::~IncomingXMLPacket( void )
{
    if (pString)
    {
        delete[] pString;
    }
}

bool IncomingXMLPacket::Decode(char* pBuffer, unsigned int uBufferSize)
{
    this->uBufferSize = uBufferSize;
    pString = new char[this->uBufferSize + 1];
    memcpy(pString, pBuffer, uBufferSize);
    pString[this->uBufferSize] = '\0';

    //

    xRoot = XMLNode::parseString(pString,"r");
    if(xRoot.isEmpty())
        return false;
    return FragmentXML();
}



const char* IncomingXMLPacket::getArgumentAsText( const char* argName, bool& updateSuccess )
{
    XMLNode xChild = xRoot.getChildNode(argName);
    if(xChild.isEmpty())
    {
        updateSuccess = false;
        return NULL;
    }
    const char* pValue = xChild.getAttribute("v");
    if (pValue == NULL)
        updateSuccess = false;
    return pValue;
}

int IncomingXMLPacket::getArgumentAsInt( const char* argName, bool& updateSuccess )
{
    XMLNode xChild = xRoot.getChildNode(argName);

    if(xChild.isEmpty())
    {
        updateSuccess = false;
        return NULL;
    }

    const char* pValue = xChild.getAttribute("v");

    if (pValue == NULL)
    {
        updateSuccess = false;
        return NULL;
    }

    return atoi(pValue);
}
double IncomingXMLPacket::getArgumentAsDouble( const char* argName, bool& updateSuccess )
{
    XMLNode xChild = xRoot.getChildNode(argName);

    if(xChild.isEmpty())
    {
        updateSuccess = false;
        return 0;
    }

    const char* pValue = xChild.getAttribute("v");

    if (pValue == NULL)
    {
        updateSuccess = false;
        return 0;
    }

    return atof(pValue);
}

bool IncomingXMLPacket::getArgumentAsBool( const char* argName, bool& updateSuccess )
{

    XMLNode xChild = xRoot.getChildNode(argName);

    if(xChild.isEmpty())
    {
        updateSuccess = false;
        return NULL;
    }

    const char* pValue = xChild.getAttribute("v");

    if (pValue == NULL)
    {
        updateSuccess = false;
        return NULL;
    }

    return strcmp(pValue, "1") == 0;
}



XMLNode IncomingXMLPacket::getInputXML()
{
    return xRoot;
}

