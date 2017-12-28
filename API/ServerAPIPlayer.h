#pragma once
#include "SerializeableQueue.h"
static class ServerAPIPlayer
{
public:
	static void GetHealth(SerializeableQueue &in, SerializeableQueue &out);
	static void GetArmor(SerializeableQueue &in, SerializeableQueue &out);
	static void GetInteriorId(SerializeableQueue &in, SerializeableQueue &out);
	static void GetYaw(SerializeableQueue &in, SerializeableQueue &out);
	static void GetX(SerializeableQueue &in, SerializeableQueue &out);
	static void GetY(SerializeableQueue &in, SerializeableQueue &out);
	static void GetZ(SerializeableQueue &in, SerializeableQueue &out);
	static void GetPosition(SerializeableQueue &in, SerializeableQueue &out);
	static void InInterior(SerializeableQueue &in, SerializeableQueue &out);
	static void InVehicle(SerializeableQueue &in, SerializeableQueue &out);
	static void IsDriver(SerializeableQueue &in, SerializeableQueue &out);
};
