#include "stdafx.h"
#include "NativeSAMPChat.h"
#include "Utils.h"

#include "DialogManager.h"

void NativeSAMPChat::Send(const std::wstring & text)
{
	DialogManager::GetInstance();

	typedef int(__stdcall *SendCommand)(const char*);
	typedef int(__stdcall *SendText)(const char*);
	static SendCommand sendCommand = (SendCommand)(Utils::GetSAMP() + 0x65C60);
	static SendText sendText = (SendText)(Utils::GetSAMP() + 0x57F0);

	if (text.length() <= 0)
		return;

	auto string = Utils::ToMultiByte(text);

	if (text[0] == L'/')
		sendCommand(string.c_str());
	else
		sendText(string.c_str());
}

void NativeSAMPChat::AddMessage(const std::wstring & text, int color)
{
	typedef int(__thiscall *AddMessage)(DWORD, int, const char*, int, int, int);
	static AddMessage addMessage = (AddMessage)(Utils::GetSAMP() + 0x64010);
	static DWORD chatPointer = Utils::GetSAMP() + 0x21A0E4;

	if (text.length() <= 0)
		return;

	auto string = Utils::ToMultiByte(text);

	addMessage(*(DWORD*)chatPointer, 4, string.c_str(), 0, color, 0);
}

std::wstring NativeSAMPChat::GetText()
{
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	DWORD inputField = *(DWORD*)(chatBox + 0x8);
	if (!inputField)
		return std::wstring();

	WORD allocatedLength = *(DWORD*)(inputField + 0x51);
	if (allocatedLength == 0x6569)
		return std::wstring();

	DWORD textPointer = *(DWORD*)(inputField + 0x4D);
	return std::wstring((const wchar_t *)textPointer, wcsnlen_s((const wchar_t*)textPointer, allocatedLength));
}

void NativeSAMPChat::SetText(const std::wstring & text)
{
	typedef int(__thiscall *AddCharacter)(DWORD, DWORD, DWORD);
	static AddCharacter addCharacter = (AddCharacter)(Utils::GetSAMP() + 0x97450);
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	DWORD inputField = *(DWORD*)(chatBox + 0x8);
	if (!inputField)
		return;

	DWORD textPointer = inputField + 0x4D;
	if (!*(DWORD*)textPointer)
		return;

	Clear();

	for (size_t i = 0; i < text.size(); i++)
		addCharacter(textPointer, i, text[i]);

	SetCursorPosition(text.size());
}

std::wstring NativeSAMPChat::GetBufferMessage(int index)
{
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	DWORD message = chatBox + 0x1565 + (0x81 * index);
	return Utils::FromMultiByte(std::string((const char*)message));
}

void NativeSAMPChat::AddBufferMessage(const std::wstring & text)
{
	typedef int(__thiscall *AddBufferMessage)(DWORD, DWORD);
	typedef int(__thiscall *DecrementBufferIndex)(DWORD);
	static AddBufferMessage addBufferMessage = (AddBufferMessage)(Utils::GetSAMP() + 0x65930);
	static DecrementBufferIndex decrementBufferIndex = (DecrementBufferIndex)(Utils::GetSAMP() + 0x65A00);
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	if (text.length() > 128)
		return;

	auto s = Utils::ToMultiByte(text);
	addBufferMessage(chatBox, (DWORD)s.c_str());

	for (int i = *(int*)(chatBox + 0x1AF0); i >= 0; i--)
		decrementBufferIndex(chatBox);
}

void NativeSAMPChat::SetCursorPosition(int index)
{
	SetCursorPosition(index, index);
}

void NativeSAMPChat::SetCursorPosition(int indexStart, int indexEnd)
{
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	DWORD inputField = *(DWORD*)(chatBox + 0x8);
	if (!inputField)
		return;

	*(DWORD*)(inputField + 0x119) = indexStart;
	*(DWORD*)(inputField + 0x11E) = indexEnd;

	if (indexEnd >= 97)
		*(DWORD*)(inputField + 0x122) = indexEnd - 97;
	else
		*(DWORD*)(inputField + 0x122) = 0;
}

void NativeSAMPChat::Toggle(bool state)
{
	typedef int(__cdecl *Toggle)(DWORD);
	static Toggle toggle = (Toggle)(Utils::GetSAMP() + 0x5D850);

	if (state && !IsOpen())
		toggle(0x75);
	else if (!state && IsOpen())
		toggle(0x75);
}

void NativeSAMPChat::Clear()
{
	typedef int(__thiscall *RemoveCharacter)(DWORD, DWORD);
	static RemoveCharacter removeCharacter = (RemoveCharacter)(Utils::GetSAMP() + 0x97500);
	static DWORD chatBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0E8);

	DWORD inputField = *(DWORD*)(chatBox + 0x8);
	if (!inputField)
		return;

	DWORD textPointer = inputField + 0x4D;
	if (!*(DWORD*)textPointer)
		return;

	for (int i = GetText().length() - 1; i >= 0; i--)
		removeCharacter(textPointer, i);

	SetCursorPosition(0);
}

bool NativeSAMPChat::IsOpen()
{
	static DWORD chat = *(DWORD*)(Utils::GetSAMP() + 0x21A10C);

	return chat && *(BYTE*)(chat + 0x55);
}