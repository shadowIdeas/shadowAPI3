#pragma once
#include <thread>
#include <functional>
#include <mutex>
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

	std::vector<std::pair<PacketIdentifier, std::function<void(int, SerializeableQueue&, SerializeableQueue&)>>> _functions;

	std::mutex _clientMutex;
	int _clientId;

	void RegisterFunctions();
	void ReadThread(HANDLE pipe);
	void WaitForClient();

	int GenerateClientId();
};
