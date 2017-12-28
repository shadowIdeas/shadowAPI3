#pragma once
static class NativePlayer
{
public:
	static float GetHealth();
	static float GetArmor();
	static int GetInteriorId();
	static float GetYaw();
	static float GetX();
	static float GetY();
	static float GetZ();

	static bool InVehicle();
	static bool InInterior();

	static bool IsDriver();

	static bool WantToGetOutOfCar();

private:
	static DWORD GetPlayer();
};
