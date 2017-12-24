#include "stdafx.h"
#include "NativePlayer.h"

#define Validation(ret) if(GetPlayer() == 0) return ret

DWORD NativePlayer::GetPlayer()
{
	return *(DWORD*)0xB6F5F0;
}

float NativePlayer::GetHealth()
{
	Validation(0.0f);

	auto health = *(float*)(GetPlayer() + 0x540);
	return health;
}

float NativePlayer::GetArmor()
{
	Validation(0.0f);

	auto armor = *(float*)(GetPlayer() + 0x548);
	return armor;
}

float NativePlayer::GetYaw()
{
	Validation(0.0f);

	auto yaw = *(float*)(GetPlayer() + 0x558);
	return yaw;
}

float NativePlayer::GetX()
{
	Validation(0.0f);

	DWORD positionPointer = *(DWORD*)(GetPlayer() + 0x14);
	if (positionPointer == 0)
		return 0.0f;

	auto x = *(float*)(positionPointer + 0x30);
	return x;
}

float NativePlayer::GetY()
{
	Validation(0.0f);

	DWORD positionPointer = *(DWORD*)(GetPlayer() + 0x14);
	if (positionPointer == 0)
		return 0.0f;

	auto y = *(float*)(positionPointer + 0x34);
	return y;
}

float NativePlayer::GetZ()
{
	Validation(0.0f);

	DWORD positionPointer = *(DWORD*)(GetPlayer() + 0x14);
	if (positionPointer == 0)
		return 0.0f;

	auto z = *(float*)(positionPointer + 0x38);
	return z;
}

bool NativePlayer::InVehicle()
{
	Validation(false);

	return (*(DWORD*)0xBA18FC) != 0;
}

bool NativePlayer::InInterior()
{
	Validation(false);

	return *(BYTE*)(GetPlayer() + 0x2F);
}

bool NativePlayer::IsDriver()
{
	Validation(false);

	if (!InVehicle())
		return false;

	if ((*(DWORD*)((*(DWORD*)0xBA18FC) + 0x460) != GetPlayer()))
		return false;

	return true;
}

bool NativePlayer::WantToGetOutOfCar()
{
	Validation(false);

	if (!InVehicle())
		return false;

	if (*(DWORD*)(GetPlayer() + 0x530) != 0)
		return false;

	return true;
}