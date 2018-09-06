#pragma once


class [!output SERVER_CLASS_NAME]: public Server, public SystemService
{
public:
	[!output SERVER_CLASS_NAME]();
	~[!output SERVER_CLASS_NAME]();

protected:
	virtual void OnStart();
	virtual void OnStop();
};

extern [!output SERVER_CLASS_NAME] theServer;
