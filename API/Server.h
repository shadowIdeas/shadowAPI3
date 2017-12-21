#pragma once
#include <thread>

class Server
{
public:
	Server();
	~Server();

private:
	HANDLE _readPipe;
	HANDLE _writePipe;

	std::thread _readThread;

	void RegisterFunctions();
	void ReadThread();

	void WaitForClient();
};
