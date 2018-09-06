#pragma once

class [!output CLIENT_CLASS_NAME] : public LogicalConnection
{
public:
	[!output CLIENT_CLASS_NAME](const char* key);
	~[!output CLIENT_CLASS_NAME]();
	SendResult PushPacket( protobuf::Message* pMessage );
	virtual const char* getKey();

private:
	string clientKey;

};




