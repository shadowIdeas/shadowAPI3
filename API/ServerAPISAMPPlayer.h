#pragma once
#include "SerializeableQueue.h"

static class ServerAPISAMPPlayer
{
public:
	SerializeFunctionH(GetLocalName);
	SerializeFunctionH(GetLocalId);
	SerializeFunctionH(GetNameById);
	SerializeFunctionH(GetIdByName);
	SerializeFunctionH(GetFullName);
};
