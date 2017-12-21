#include "stdafx.h"
#include "ClientMessage.h"
#include "API.h"

ClientMessage::ClientMessage()
{
}

ClientMessage::~ClientMessage()
{
}

SerializeableQueue & ClientMessage::GetInput()
{
	return _in;
}

SerializeableQueue & ClientMessage::GetResponse(PacketIdentifier identifier)
{
	return _out;
}