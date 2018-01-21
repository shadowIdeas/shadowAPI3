#include "stdafx.h"
#include "NativeSAMPPlayer.h"
#include "Utils.h"

#include <algorithm>

#define Validation(ret) if(GetPlayer() == 0) return ret

std::wstring NativeSAMPPlayer::GetLocalName()
{
	Validation(std::wstring());
	auto player = GetPlayer();

	DWORD a1 = *(DWORD*)(player + 0x3CD);
	if (!a1)
		return std::wstring();

	DWORD a2 = *(DWORD*)(a1 + 0x18);
	if (!a2)
		return std::wstring();

	DWORD nameLength = *(DWORD*)(a2 + 0x1E);

	DWORD namePointer = 0;
	if (nameLength >= 16)
		namePointer = *(DWORD*)(a2 + 0xA);
	else
		namePointer = a2 + 0xA;

	if (namePointer == 0)
		return std::wstring();

	return Utils::FromMultiByte((const char*)namePointer);
}

int NativeSAMPPlayer::GetLocalId()
{
	Validation(-1);
	auto player = GetPlayer();

	DWORD a1 = *(DWORD*)(player + 0x3CD);
	if (!a1)
		return -1;

	DWORD a2 = *(DWORD*)(a1 + 0x18);
	if (!a2)
		return -1;

	return *(WORD*)(a2 + 0x4);
}

std::wstring NativeSAMPPlayer::GetNameById(int id)
{
	Validation(std::wstring());

	if (id > 500)
		return std::wstring();

	auto player = GetPlayer();

	DWORD a1 = *(DWORD*)(player + 0x3CD);
	if (!a1)
		return std::wstring();

	DWORD a2 = *(DWORD*)(a1 + 0x18);
	if (!a2)
		return std::wstring();

	DWORD remotePlayer = *(DWORD*)(a2 + 0x2E + (id * 4));
	if (!remotePlayer)
		return std::wstring();

	DWORD nameLength = *(DWORD*)(remotePlayer + 0x20);
	DWORD namePointer = 0;
	if (nameLength >= 16)
		namePointer = *(DWORD*)(remotePlayer + 0xC);
	else
		namePointer = remotePlayer + 0xC;

	if (namePointer == 0)
		return std::wstring();

	return Utils::FromMultiByte((const char*)namePointer);
}

int NativeSAMPPlayer::GetIdByName(const std::wstring & name)
{
	Validation(-1);

	std::wstring searchName = name;
	std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::towupper);

	for (size_t i = 0; i < 500; i++)
	{
		auto name = GetNameById(i);
		std::transform(name.begin(), name.end(), name.begin(), ::towupper);

		if (searchName == name)
			return i;
	}

	return -1;
}

std::wstring NativeSAMPPlayer::GetFullName(const std::wstring & name)
{
	Validation(std::wstring());

	std::wstring searchName = name;
	std::transform(searchName.begin(), searchName.end(), searchName.begin(), ::towupper);

	for (size_t i = 0; i < 500; i++)
	{
		auto currentName = GetNameById(i);
		auto upperName = currentName;
		std::transform(upperName.begin(), upperName.end(), upperName.begin(), ::towupper);

		if (upperName.find(searchName) != std::wstring::npos)
			return currentName;
	}

	return std::wstring();
}

DWORD NativeSAMPPlayer::GetPlayer()
{
	static DWORD samp = Utils::GetSAMP();
	return *(DWORD*)(samp + 0x21A0F8);
}