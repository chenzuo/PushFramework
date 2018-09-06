#pragma once
class WebsocketContext : public ProtocolContext
{
public:
	WebsocketContext(void);
	~WebsocketContext(void);

	virtual void recycle();

	RecyclableBuffer bufferedContent;
	int currentContinuationOpCode;
};

