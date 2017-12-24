#include "stdafx.h"
#include "ServerAPIVehicle.h"
#include "NativeVehicle.h"

void ServerAPIVehicle::GetSpeed(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativeVehicle::GetSpeed());
}

void ServerAPIVehicle::GetHealth(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativeVehicle::GetHealth());
}

void ServerAPIVehicle::GetModelId(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeVehicle::GetModelId());
}

void ServerAPIVehicle::IsLightActive(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeVehicle::IsLightActive());
}

void ServerAPIVehicle::IsLocked(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeVehicle::IsLocked());
}

void ServerAPIVehicle::IsEngineRunning(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeVehicle::IsEngineRunning());
}

void ServerAPIVehicle::UseHorn(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeVehicle::UseHorn());
}

void ServerAPIVehicle::UseSiren(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeVehicle::UseSiren());
}