#pragma once
#include "SerializeableQueue.h"
#include "PacketIdentifier.h"
#include <memory>

class ClientMessage
{
public:
	ClientMessage(PacketIdentifier identifier);
	~ClientMessage();

	void SetResponse(std::shared_ptr<SerializeableQueue> response);

	SerializeableQueue &GetInput();
	std::shared_ptr<SerializeableQueue> GetResponse();
private:
	SerializeableQueue _in;
	std::shared_ptr<SerializeableQueue> _out;
};
