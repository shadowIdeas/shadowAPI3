#pragma once
#include "SerializeableQueue.h"
#include "PacketIdentifier.h"

class ClientMessage
{
public:
	ClientMessage();
	~ClientMessage();

	SerializeableQueue &GetInput();
	SerializeableQueue &GetResponse(PacketIdentifier identifier);
private:
	SerializeableQueue _in;
	SerializeableQueue _out;
};
