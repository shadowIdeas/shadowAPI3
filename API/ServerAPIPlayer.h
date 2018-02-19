#pragma once
#include "SerializeableQueue.h"
static class ServerAPIPlayer
{
public:
	SerializeFunctionH(GetHealth);
	SerializeFunctionH(GetArmor);
	SerializeFunctionH(GetInteriorId);
	SerializeFunctionH(GetYaw);
	SerializeFunctionH(GetX);
	SerializeFunctionH(GetY);
	SerializeFunctionH(GetZ);
	SerializeFunctionH(GetPosition);
	SerializeFunctionH(InInterior);
	SerializeFunctionH(InVehicle);
	SerializeFunctionH(IsDriver);
};
