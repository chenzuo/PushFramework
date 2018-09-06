#include "StdAfx.h"
#include "DemoPublisher.h"
#include "MyServer.h"

#define nMaximumMessageSize 100 // The maximum size of an abstract message after being encoded.

DemoPublisher::DemoPublisher(void)
{
}

DemoPublisher::~DemoPublisher(void)
{
}

void DemoPublisher::start()
{
	hKillEvent	= CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD	dwThreadId = 0;
	hThread = CreateThread(NULL, // Security
		0,					// default stack size
		threadProc,  // thread proc
		(void*) this,
		0,					// init flag
		&dwThreadId);
}

void DemoPublisher::stop()
{
	::SetEvent(hKillEvent);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
}

DWORD WINAPI DemoPublisher::threadProc( LPVOID lpVoid )
{
	DemoPublisher* pMe = (DemoPublisher*) lpVoid;
	pMe->doJob();
	return 0;
}

// We should not exceed the nMaximumMessageSize size for a particular message.
// 100 is there to make room for the WS header bytes.

string gen_random() {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string s;

	for (int i = 0; i < (nMaximumMessageSize); ++i) {
		s+= alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return s;
}

extern MyServer theServer;
void DemoPublisher::doJob()
{
	unsigned int counter = 1;
	while (true)
	{
		DWORD dwRet = WaitForSingleObject(hKillEvent, 10);

		//If kill event then quit loop :
		if (dwRet != WAIT_TIMEOUT)
		{
			break;
		}

		//
		/*XMLMessage* response = new XMLMessage(1);
		string text = gen_random();
		response->setArgumentAsText("text", text.c_str());
		response->setArgumentAsInt("hash", hash(text.c_str()));
		response->setArgumentAsInt("id", ++counter);

		theServer.PushPacket(response, "queue1");*/

	}
}


unsigned int DemoPublisher::hash( const char *str )
{
	unsigned int hash = 0;
	int c;

	while (c = *str++)
		hash += c;

	return hash;
}
