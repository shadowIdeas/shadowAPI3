#include "stdafx.h"
#include "Utils.h"

DWORD Utils::DetourNaked(DWORD originalAddress, DWORD newAddress, int length)
{
	DWORD oldProtection;

	VirtualProtect((void*)originalAddress, length, PAGE_EXECUTE_READWRITE, &oldProtection);

	for (size_t i = 0; i < length; i++)
		*(BYTE*)(originalAddress + i) = 0x90;

	DWORD relativeJumpAddress = (newAddress - originalAddress) - 5;

	*(BYTE*)(originalAddress + 0) = 0xE9;
	*(DWORD*)(originalAddress + 1) = relativeJumpAddress;

	VirtualProtect((void*)originalAddress, length, oldProtection, 0);

	return originalAddress + length;
}

std::string Utils::ToMultiByte(const std::wstring & wide)
{
	int length = wide.length();

	if (length <= 0)
		return std::string();

	auto nativeMultiByte = std::unique_ptr<char>(new char[length + 1]);
	nativeMultiByte.get()[length] = '\0';
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wide.c_str(), length, nativeMultiByte.get(), length, 0, 0);

	std::string newString = std::string(nativeMultiByte.get());
	return newString;
}

std::wstring Utils::FromMultiByte(const std::string & multiByte)
{
	int length = multiByte.length();

	if (length <= 0)
		return std::wstring();

	auto nativeWideString = std::unique_ptr<wchar_t>(new wchar_t[length + 1]);
	nativeWideString.get()[length] = '\0';
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, multiByte.c_str(), length, nativeWideString.get(), length);

	std::wstring newString = std::wstring(nativeWideString.get());
	return newString;
}

DWORD Utils::GetSAMP()
{
	return (DWORD)GetModuleHandle(L"samp.dll");
}