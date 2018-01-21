#pragma once
#include "SerializeableQueue.h"
static class ServerAPIVehicle
{
public:
	static void GetSpeed(SerializeableQueue &in, SerializeableQueue &out);
	static void GetHealth(SerializeableQueue &in, SerializeableQueue &out);
	static void GetModelId(SerializeableQueue &in, SerializeableQueue &out);
	static void IsLightActive(SerializeableQueue &in, SerializeableQueue &out);
	static void IsLocked(SerializeableQueue &in, SerializeableQueue &out);
	static void IsEngineRunning(SerializeableQueue &in, SerializeableQueue &out);
	static void UseHorn(SerializeableQueue &in, SerializeableQueue &out);
	static void UseSiren(SerializeableQueue &in, SerializeableQueue &out);
};
