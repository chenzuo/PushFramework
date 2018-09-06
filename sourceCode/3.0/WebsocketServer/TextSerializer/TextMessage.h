#pragma once

#include "Symbols.h"
class TEXTSERIALIZER_API TextMessage : public OutgoingPacket, public IncomingPacket
{
public:
	TextMessage(const char* content, unsigned int size);
	~TextMessage();
	char* getContent();
	unsigned int getSize();

private:
	char* content;
	unsigned int size;
};
