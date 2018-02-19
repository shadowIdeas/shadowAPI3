#pragma once
#include "SerializeableQueue.h"
static class ServerAPIOverlayText
{
public:
	SerializeFunctionH(Create);
	SerializeFunctionH(Delete);
	SerializeFunctionH(SetColor);
	SerializeFunctionH(SetX);
	SerializeFunctionH(SetY);
	SerializeFunctionH(SetMaxWidth);
	SerializeFunctionH(SetMaxHeight);
	SerializeFunctionH(SetActive);
	SerializeFunctionH(SetText);
	SerializeFunctionH(SetSize);
	SerializeFunctionH(SetUseMaxWidth);
	SerializeFunctionH(SetUseMaxHeight);
	SerializeFunctionH(GetExtent);
};
