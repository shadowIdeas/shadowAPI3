#pragma once
static class NativeSAMPPlayer
{
public:
	static std::wstring GetLocalName();
	static int GetLocalId();

	static std::wstring GetNameById(int id);
	static int GetIdByName(const std::wstring &name);
	static std::wstring GetFullName(const std::wstring & name);
private:
	static DWORD GetPlayer();
};
