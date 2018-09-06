#include "stdafx.h"
#include "TextMessage.h"



TextMessage::TextMessage( const char* _content, unsigned int _size )
{
	this->size = _size;
	this->content = NULL;

	if (size != 0)
	{
		content = new char[size];
		memcpy(content, _content, size);
	}
}

char* TextMessage::getContent()
{
	return content;
}

unsigned int TextMessage::getSize()
{
	return size;
}

TextMessage::~TextMessage()
{
	if (content)
	{
		delete [] content;
	}
}

