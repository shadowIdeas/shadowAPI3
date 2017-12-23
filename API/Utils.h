#pragma once
#include <memory>

static class Utils
{
public:
	static DWORD DetourNaked(DWORD originalAddress, DWORD newAddress, int length);
	static DWORD Detour(DWORD originalAddress, DWORD newAddress, int length);
	static std::string ToMultiByte(const std::wstring &wide);
	static std::wstring FromMultiByte(const std::string &multiByte);
	static DWORD GetSAMP();
};
