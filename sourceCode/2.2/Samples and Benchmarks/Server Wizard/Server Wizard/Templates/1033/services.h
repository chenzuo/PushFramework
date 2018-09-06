#pragma once

class [!output SERVICE_ECHO_CLASS] : public Service
{
public:
	[!output SERVICE_ECHO_CLASS]();
	~[!output SERVICE_ECHO_CLASS]();
protected:
	 virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};

class [!output SERVICE_REDIRECT_CLASS] : public Service
{
public:
	[!output SERVICE_REDIRECT_CLASS]();
	~[!output SERVICE_REDIRECT_CLASS]();

protected:
	virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};

class [!output SERVICE_BROADCAST_CLASS] : public Service
{
public:
	[!output SERVICE_BROADCAST_CLASS]();
	~[!output SERVICE_BROADCAST_CLASS]();

protected:
	virtual void handle(LogicalConnection* pClient, IncomingPacket* pRequest);
};