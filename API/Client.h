#pragma once
#include <thread>

class Client
{
public:
	Client();
	~Client();
private:
	HANDLE _readPipe;
	HANDLE _writePipe;
	std::thread _readThread;

	void ReadThread();
};
