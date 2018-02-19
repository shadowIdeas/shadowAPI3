#pragma once
#include "SerializeableQueue.h"
static class ServerAPIOverlayBox
{
public:
	SerializeFunctionH(Create);
	SerializeFunctionH(Delete);
	SerializeFunctionH(SetColor);
	SerializeFunctionH(SetX);
	SerializeFunctionH(SetY);
	SerializeFunctionH(SetWidth);
	SerializeFunctionH(SetHeight);
	SerializeFunctionH(SetActive);
};
