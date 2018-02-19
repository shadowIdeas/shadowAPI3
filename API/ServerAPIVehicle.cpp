#include "stdafx.h"
#include "ServerAPIVehicle.h"
#include "NativeVehicle.h"

SerializeFunction(ServerAPIVehicle::GetSpeed)
{
	out.WriteFloat(NativeVehicle::GetSpeed());
}

SerializeFunction(ServerAPIVehicle::GetHealth)
{
	out.WriteFloat(NativeVehicle::GetHealth());
}

SerializeFunction(ServerAPIVehicle::GetModelId)
{
	out.WriteInteger(NativeVehicle::GetModelId());
}

SerializeFunction(ServerAPIVehicle::IsLightActive)
{
	out.WriteBoolean(NativeVehicle::IsLightActive());
}

SerializeFunction(ServerAPIVehicle::IsLocked)
{
	out.WriteBoolean(NativeVehicle::IsLocked());
}

SerializeFunction(ServerAPIVehicle::IsEngineRunning)
{
	out.WriteBoolean(NativeVehicle::IsEngineRunning());
}

SerializeFunction(ServerAPIVehicle::UseHorn)
{
	out.WriteBoolean(NativeVehicle::UseHorn());
}

SerializeFunction(ServerAPIVehicle::UseSiren)
{
	out.WriteBoolean(NativeVehicle::UseSiren());
}