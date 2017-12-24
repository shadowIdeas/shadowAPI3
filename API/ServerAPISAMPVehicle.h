#pragma once
#include "SerializeableQueue.h"
static class ServerAPISAMPVehicle
{
public:
	static void GetNumberplate(SerializeableQueue &in, SerializeableQueue &out);
	static void ToggleSiren(SerializeableQueue &in, SerializeableQueue &out);
};
