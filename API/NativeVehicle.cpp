#include "stdafx.h"
#include "NativeVehicle.h"

#define Validation(ret) if(GetVehicle() == 0) return ret

float NativeVehicle::GetSpeed()
{
	Validation(0.0f);

	auto vehicle = GetVehicle();

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	x = *(float*)(vehicle + 0x44);
	y = *(float*)(vehicle + 0x48);
	z = *(float*)(vehicle + 0x4C);

	return pow((pow(x, 2.0f) + pow(y, 2.0f) + pow(z, 2.0f)), 0.5f) * 1.42f * 100.0f;
}

float NativeVehicle::GetHealth()
{
	Validation(0.0f);

	auto vehicle = GetVehicle();

	float health = *(float*)(vehicle + 0x4C0);
	return health;
}

int NativeVehicle::GetModelId()
{
	Validation(0);

	auto vehicle = GetVehicle();

	WORD modelId = *(WORD*)(vehicle + 0x22);
	return modelId;
}

bool NativeVehicle::IsLightActive()
{
	Validation(false);

	auto vehicle = GetVehicle();

	DWORD flags = *(DWORD*)(vehicle + 0x428);
	return flags & 64;
}

bool NativeVehicle::IsLocked()
{
	Validation(false);

	auto vehicle = GetVehicle();

	DWORD flags = *(DWORD*)(vehicle + 0x4F8);
	return flags & 2;
}

bool NativeVehicle::IsEngineRunning()
{
	Validation(false);

	auto vehicle = GetVehicle();

	DWORD flags = *(DWORD*)(vehicle + 0x428);
	return flags & 16;
}

bool NativeVehicle::UseHorn()
{
	Validation(false);

	auto vehicle = GetVehicle();

	DWORD flags = *(DWORD*)(vehicle + 0x514);
	return flags & 1;
}

bool NativeVehicle::UseSiren()
{
	Validation(false);

	auto vehicle = GetVehicle();

	BYTE flags = *(BYTE*)(vehicle + 0x42D);
	return flags & 128;
}

DWORD NativeVehicle::GetVehicle()
{
	return *(DWORD*)0xBA18FC;
}