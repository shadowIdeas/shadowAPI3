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
	std::vector<std::unique_ptr<std::thread>> _readThreads;
	std::thread _incomingThread;

	std::vector<std::pair<PacketIdentifier, std::function<void(SerializeableQueue&, SerializeableQueue&)>>> _functions;

	void RegisterFunctions();
	void ReadThread(HANDLE pipe);
	void WaitForClient();
};
