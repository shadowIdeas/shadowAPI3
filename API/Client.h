#pragma once
#include <thread>
#include <atomic>
#include "SerializeableQueue.h"
#include "ClientMessage.h"
#include <condition_variable>

class Client
{
public:
	Client();
	~Client();

	std::shared_ptr<ClientMessage> CreateMessage(PacketIdentifier identifier);
	void Write(std::shared_ptr<ClientMessage> message);
private:
	HANDLE _readPipe;
	HANDLE _writePipe;
	std::thread _readThread;
	std::atomic<bool> _running;
	HANDLE _events[128];
	std::atomic<bool> _used[128];
	std::shared_ptr<SerializeableQueue> _out[128];

	std::mutex _mutex;

	void ReadThread();
};
