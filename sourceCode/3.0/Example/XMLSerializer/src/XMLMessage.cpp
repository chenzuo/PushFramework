#include "stdafx.h"
#include "XMLMessage.h"


XMLMessage::~XMLMessage()
{

}

XMLMessage::XMLMessage(int typeId)
{
	xmlRoot = XMLNode::createXMLTopNode("root");

	std::stringstream ss;
	ss << typeId;

	xmlRoot.addAttribute("typeId", ss.str().c_str());
}

XMLMessage::XMLMessage()
{
}


XMLNode& XMLMessage::getRoot()
{
	return xmlRoot;
}

void XMLMessage::Encode()
{
	if(!data.empty())
		return;

	int nSize;
	char *pString = xmlRoot.createXMLString(0, &nSize);
	data = pString;

	delete [] pString;
}

const char* XMLMessage::getArgumentAsText( const char* argName )
{
	if (xmlRoot.isEmpty())
		return "";
	XMLNode xChild = xmlRoot.getChildNode(argName);
	if (xChild.isEmpty())
	{
		return "";
	}
	const char* val = xChild.getAttribute("val");
	if (val == NULL)
		return "";
	return val;
}

int XMLMessage::getArgumentAsInt( const char* argName )
{
	return atoi(getArgumentAsText(argName));
}
bool XMLMessage::getArgumentAsBool( const char* argName )
{
	return getArgumentAsInt(argName) == 1;
}
void XMLMessage::setArgumentAsText( const char* argName, const char* val )
{
	if (xmlRoot.isEmpty())
		return;
	xmlRoot.addChild(argName).addAttribute("val", val);
}

void XMLMessage::setArgumentAsInt( const char* argName, int val )
{
	std::stringstream ss;
	ss << val;
	setArgumentAsText(argName, ss.str().c_str());
}

void XMLMessage::setArgumentAsBool( const char* argName, bool val )
{
	setArgumentAsText(argName, val ? "1" : "0");
}

std::string& XMLMessage::getData()
{
	return data;
}

int XMLMessage::getTypeId()
{
	const char* val = xmlRoot.getAttribute("typeId");
	return atoi(val);
}

XMLMessage* XMLMessage::CreateFromBuffer( const char* stringBuffer )
{
	XMLNode xmlRoot = XMLNode::parseString(stringBuffer, "root");
	if (xmlRoot.isEmpty())
	{
		return NULL;
	}

	const char* val = xmlRoot.getAttribute("typeId");
	if(!val)
		return NULL;

	XMLMessage* message = new XMLMessage();
	message->xmlRoot = xmlRoot;

	return message;
}
