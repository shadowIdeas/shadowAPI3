#pragma once
#include <thread>
#include <functional>
#include "PacketIdentifier.h"
#include "SerializeableQueue.h"

class Server
{
public:
	Server();
	~Server();

private:
	HANDLE _readPipe;
	HANDLE _writePipe;

	std::thread _readThread;

	std::vector<std::pair<PacketIdentifier, std::function<void(SerializeableQueue&, SerializeableQueue&)>>> _functions;

	void RegisterFunctions();
	void ReadThread();

	void WaitForClient();
};
