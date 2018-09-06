#pragma once

#include "xmlParser.h"
#include "Symbols.h"
class XMLSERIALIZER_API XMLMessage : public IncomingPacket, public OutgoingPacket
{
public:
	XMLMessage(int typeId);
	virtual ~XMLMessage();
private:
	XMLMessage();

public:
	static XMLMessage* CreateFromBuffer(const char* stringBuffer);
	void Encode();

public:

	int getTypeId();
	XMLNode& getRoot();
	

	const char* getArgumentAsText(const char* argName);
	int getArgumentAsInt(const char* argName);
	bool getArgumentAsBool(const char* argName);
	void setArgumentAsText(const char* argName, const char* val);
	void setArgumentAsInt(const char* argName, int val);
	void setArgumentAsBool(const char* argName, bool val);

	std::string& getData();

private:
	XMLNode xmlRoot;
	std::string data;
};