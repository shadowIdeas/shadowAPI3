#include "stdafx.h"
#include "ClientMessage.h"
#include "API.h"

ClientMessage::ClientMessage(PacketIdentifier identifier)
{
	_in.WriteInteger((int)identifier);
}

ClientMessage::~ClientMessage()
{
}

void ClientMessage::SetResponse(std::shared_ptr<SerializeableQueue> response)
{
	_out = response;
}

SerializeableQueue & ClientMessage::GetInput()
{
	return _in;
}

std::shared_ptr<SerializeableQueue> ClientMessage::GetResponse()
{
	return _out;
}