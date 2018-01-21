#include "stdafx.h"
#include "NativeSAMPVehicle.h"
#include "Utils.h"
#include "NativePlayer.h"

#define Validation(ret) if(GetVehicle() == 0) return ret

std::wstring NativeSAMPVehicle::GetNumberplate()
{
	Validation(std::wstring());

	typedef int(__thiscall *Convert)(DWORD, DWORD);
	static Convert convert = (Convert)(Utils::GetSAMP() + 0x1B0A0);
	DWORD gtaVehicle = *(DWORD*)0xBA18FC;
	auto vehicle = GetVehicle();

	DWORD a1 = *(DWORD*)(vehicle + 0x3CD);
	if (!a1)
		return std::wstring();

	DWORD a2 = *(DWORD*)(a1 + 0x1C);
	if (!a2)
		return std::wstring();

	if (!NativePlayer::InVehicle())
		return std::wstring();

	int id = convert(a2, gtaVehicle);

	if (id == -1)
		return std::wstring();

	DWORD a3 = *(DWORD*)(a2 + 0x1134 + (id * 4));

	if (!a3)
		return std::wstring();

	DWORD a4 = a3 + 0x93;

	return Utils::FromMultiByte((const char*)a4);
}

void NativeSAMPVehicle::ToggleSiren(bool state)
{
	Validation();
	typedef int(__thiscall *Convert)(DWORD, DWORD);
	typedef int(__thiscall *Toggle)(DWORD, BYTE);
	static Convert convert = (Convert)(Utils::GetSAMP() + 0x1B0A0);
	static Toggle toggle = (Toggle)(Utils::GetSAMP() + 0xB0FF0);
	DWORD gtaVehicle = *(DWORD*)0xBA18FC;
	auto vehicle = GetVehicle();

	DWORD a1 = *(DWORD*)(vehicle + 0x3CD);
	if (!a1)
		return;

	DWORD a2 = *(DWORD*)(a1 + 0x1C);
	if (!a2)
		return;

	if (!NativePlayer::InVehicle() || !NativePlayer::IsDriver())
		return;

	int id = convert(a2, gtaVehicle);

	if (id == -1)
		return;

	DWORD a3 = *(DWORD*)(a2 + 0x1134 + (id * 4));

	if (!a3)
		return;

	toggle(a3, state);
}

DWORD NativeSAMPVehicle::GetVehicle()
{
	static DWORD samp = Utils::GetSAMP();
	return *(DWORD*)(samp + 0x21A0F8);
}