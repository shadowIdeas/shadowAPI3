#include "stdafx.h"
#include "ClientMessage.h"
#include "API.h"

ClientMessage::ClientMessage(PacketIdentifier identifier)
{
	_invalid = false;
	_in.WriteInteger((int)identifier);
}

ClientMessage::~ClientMessage()
{
}

void ClientMessage::SetResponse(std::shared_ptr<SerializeableQueue> response)
{
	_out = response;
}

void ClientMessage::Invalidate()
{
	_invalid = true;
}

SerializeableQueue & ClientMessage::GetInput()
{
	return _in;
}

std::shared_ptr<SerializeableQueue> ClientMessage::GetResponse()
{
	return _out;
}

bool ClientMessage::IsInvalid()
{
	return _invalid;
}
