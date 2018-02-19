#pragma once
#include "SerializeableQueue.h"

static class ServerAPISAMPChat
{
public:
	SerializeFunctionH(Send);
	SerializeFunctionH(AddMessage1);
	SerializeFunctionH(AddMessage2);

	SerializeFunctionH(GetText);
	SerializeFunctionH(SetText);

	SerializeFunctionH(GetBufferMessage);
	SerializeFunctionH(AddBufferMessage);

	SerializeFunctionH(SetCursorPosition);
	SerializeFunctionH(SetCursorPosition2);

	SerializeFunctionH(Toggle);
	SerializeFunctionH(Clear);

	SerializeFunctionH(IsOpen);
};
