#pragma once
#include "SerializeableQueue.h"
static class ServerAPIVehicle
{
public:
	SerializeFunctionH(GetSpeed);
	SerializeFunctionH(GetHealth);
	SerializeFunctionH(GetModelId);
	SerializeFunctionH(IsLightActive);
	SerializeFunctionH(IsLocked);
	SerializeFunctionH(IsEngineRunning);
	SerializeFunctionH(UseHorn);
	SerializeFunctionH(UseSiren);
};
