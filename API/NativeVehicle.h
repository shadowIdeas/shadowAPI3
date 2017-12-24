#pragma once
static class NativeVehicle
{
public:
	static float GetSpeed();
	static float GetHealth();
	static int GetModelId();

	static bool IsLightActive();
	static bool IsLocked();
	static bool IsEngineRunning();

	static bool UseHorn();
	static bool UseSiren();
private:
	static DWORD GetVehicle();
};
