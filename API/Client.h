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

	int FastReadInteger(PacketIdentifier identifier);
	float FastReadFloat(PacketIdentifier identifier);
	bool FastReadBoolean(PacketIdentifier identifier);
	std::wstring FastReadString(PacketIdentifier identifier);
	void FastWriteVoid(PacketIdentifier identifier);
	void FastWriteInteger(PacketIdentifier identifier, int i);
	void FastWriteBoolean(PacketIdentifier identifier, bool b);
	void FastWriteString(PacketIdentifier identifier, const std::wstring &s);
private:
	HANDLE _pipe;
	std::thread _readThread;
	std::atomic<bool> _running;
	HANDLE _events[62];
	HANDLE _communicationEvents[64];
	std::vector<BYTE> _communicationData[62];
	std::atomic<bool> _used[62];
	std::mutex _idMutex;
	std::shared_ptr<SerializeableQueue> _out[62];
	std::atomic<bool> _freed;

	std::mutex _mutex;

	void CommunicationThread();
	void Free();
};
