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
	void Invalidate();

	SerializeableQueue &GetInput();
	std::shared_ptr<SerializeableQueue> GetResponse();
	bool IsInvalid();
private:
	SerializeableQueue _in;
	std::shared_ptr<SerializeableQueue> _out;
	bool _invalid;
};
