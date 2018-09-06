#pragma once

class DemoPublisher
{
public:
	DemoPublisher(void);
	~DemoPublisher(void);

	void start();

	void stop();

	void doJob();

	static DWORD WINAPI threadProc(LPVOID lpVoid);

private:
	HANDLE hThread;
	HANDLE	hKillEvent;//kill event.

	unsigned int hash(const char *str);
};
