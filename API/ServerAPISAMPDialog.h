#pragma once
#include "SerializeableQueue.h"
static class ServerAPISAMPDialog
{
public:
	SerializeFunctionH(GetText);
	SerializeFunctionH(SetText);
	SerializeFunctionH(SetCursorPosition1);
	SerializeFunctionH(SetCursorPosition2);
	SerializeFunctionH(GetId);
	SerializeFunctionH(GetStringCount);
	SerializeFunctionH(GetStringByIndex);
	SerializeFunctionH(Clear);
	SerializeFunctionH(Close);
	SerializeFunctionH(SelectIndex);
	SerializeFunctionH(IsOpen);
	SerializeFunctionH(BlockGetCaption);
	SerializeFunctionH(BlockGetText);
	SerializeFunctionH(Block);
	SerializeFunctionH(BlockHasBlockedDialog);
	SerializeFunctionH(BlockHasNeedBlocking);
};
