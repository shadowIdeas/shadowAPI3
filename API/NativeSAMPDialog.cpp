#include "stdafx.h"
#include "NativeSAMPDialog.h"
#include "Utils.h"

#include "DialogManager.h"

std::wstring NativeSAMPDialog::GetText()
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 1)
		return std::wstring();

	DWORD inputField = *(DWORD*)(dialogBox + 0x24);

	WORD allocatedLength = *(DWORD*)(inputField + 0x51);
	if (allocatedLength == 0x6569)
		return std::wstring();

	DWORD textPointer = *(DWORD*)(inputField + 0x4D);

	return std::wstring((const wchar_t *)textPointer, allocatedLength);
}

void NativeSAMPDialog::SetText(const std::wstring & text)
{
	typedef int(__thiscall *AddCharacter)(DWORD, DWORD, DWORD);
	static AddCharacter addCharacter = (AddCharacter)(Utils::GetSAMP() + 0x97450);
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 1)
		return;

	DWORD inputField = *(DWORD*)(dialogBox + 0x24);
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

void NativeSAMPDialog::SetCursorPosition(int index)
{
	SetCursorPosition(index, index);
}

void NativeSAMPDialog::SetCursorPosition(int indexStart, int indexEnd)
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 1)
		return;

	DWORD inputField = *(DWORD*)(dialogBox + 0x24);
	if (!inputField)
		return;

	*(DWORD*)(inputField + 0x119) = indexStart;
	*(DWORD*)(inputField + 0x11E) = indexEnd;
}

int NativeSAMPDialog::GetId()
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	return *(DWORD*)(dialogBox + 0x30);
}

int NativeSAMPDialog::GetStringCount()
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 2)
		return 0;

	DWORD tabList = *(DWORD*)(dialogBox + 0x20);
	if (!tabList)
		return 0;

	return *(DWORD*)(tabList + 0x150);
}

std::wstring NativeSAMPDialog::GetStringByIndex(int index)
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 2)
		return std::wstring();

	DWORD tabList = *(DWORD*)(dialogBox + 0x20);
	if (!tabList)
		return std::wstring();

	DWORD stringPool = *(DWORD*)(tabList + 0x14C);
	if (!stringPool)
		return std::wstring();

	DWORD stringPointer = *(DWORD*)(stringPool + (index * 4));

	return Utils::FromMultiByte(std::string((const char*)stringPointer));
}

void NativeSAMPDialog::Clear()
{
	typedef int(__thiscall *RemoveCharacter)(DWORD, DWORD);
	static RemoveCharacter removeCharacter = (RemoveCharacter)(Utils::GetSAMP() + 0x97500);
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 1)
		return;

	DWORD inputField = *(DWORD*)(dialogBox + 0x24);
	if (!inputField)
		return;

	DWORD textPointer = inputField + 0x4D;
	if (!*(DWORD*)textPointer)
		return;

	for (int i = GetText().length() - 1; i >= 0; i--)
		removeCharacter(textPointer, i);

	SetCursorPosition(0);
}

void NativeSAMPDialog::Close(int reason)
{
	typedef int(__thiscall *Close)(DWORD, BYTE);
	static Close close = (Close)(Utils::GetSAMP() + 0x6C040);
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	close(dialogBox, (BYTE)reason);
}

void NativeSAMPDialog::SelectIndex(int index)
{
	typedef int(__thiscall *SelectIndex)(DWORD, DWORD);
	static SelectIndex selectIndex = (SelectIndex)(Utils::GetSAMP() + 0x863C0);
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	if (*(DWORD*)(dialogBox + 0x2C) != 2)
		return;

	DWORD tabList = *(DWORD*)(dialogBox + 0x20);
	if (!tabList)
		return;

	selectIndex(tabList, index);
}

bool NativeSAMPDialog::IsOpen()
{
	static DWORD dialogBox = *(DWORD*)(Utils::GetSAMP() + 0x21A0B8);

	return *(BYTE*)(dialogBox + 0x28);
}

std::wstring NativeSAMPDialog::BlockGetCaption()
{
	return DialogManager::GetInstance().GetCaption();
}

std::wstring NativeSAMPDialog::BlockGetText()
{
	return DialogManager::GetInstance().GetText();
}

void NativeSAMPDialog::Block(int id, const std::wstring & text)
{
	return DialogManager::GetInstance().StartBlock(id, text);
}

bool NativeSAMPDialog::BlockHasBlockedDialog()
{
	return DialogManager::GetInstance().HasBlocked();
}

bool NativeSAMPDialog::BlockHasNeedBlocking()
{
	return false;
}