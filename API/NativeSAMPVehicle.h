#pragma once
static class NativeSAMPVehicle
{
public:
	static std::wstring GetNumberplate();
	static void ToggleSiren(bool state);
private:
	static DWORD GetVehicle();
};
