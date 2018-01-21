#include "stdafx.h"
#include "DialogManager.h"
#include "Utils.h"
#include "NativeSAMPDialog.h"

typedef int(__thiscall *Open)(void *dialog, int a1, int a2, char *caption, char *text, char *button1, char *button2, int a3);
Open original;

int __fastcall OpenHook(void *dialog, void* edx, int a1, int a2, char *caption, char *text, char *button1, char *button2, int a3)
{
	auto convCaption = Utils::FromMultiByte(caption);
	auto convText = Utils::FromMultiByte(text);

	if (DialogManager::GetInstance().ShouldBlock(a1, convCaption, convText))
		return 0;

	return original(dialog, a1, a2, caption, text, button1, button2, a3);
}

DialogManager::DialogManager()
{
	_blockActive = false;
	_blockId = 0;
	_blockCaption = std::wstring();

	original = (Open)Utils::Detour(Utils::GetSAMP() + 0x6B9C0, (DWORD)&OpenHook, 5);
}

DialogManager::~DialogManager()
{
}

DialogManager & DialogManager::GetInstance()
{
	static DialogManager instance;
	return instance;
}

void DialogManager::StartBlock(int id, const std::wstring & caption)
{
	_caption = std::wstring();
	_text = std::wstring();

	_blockId = id;
	_blockCaption = caption;
	_blockActive = true;
}

bool DialogManager::ShouldBlock(int id, const std::wstring & caption, const std::wstring &text)
{
	if (!_blockActive)
		return false;

	if (_blockId != id)
		return false;

	if (caption.find(_blockCaption) == std::wstring::npos)
		return false;

	_caption = caption;
	_text = text;

	_blockActive = false;
	return true;
}

bool DialogManager::HasBlocked()
{
	return _blockActive == false && (!_caption.empty() || !_text.empty());
}

const std::wstring & DialogManager::GetCaption()
{
	return _caption;
}

const std::wstring & DialogManager::GetText()
{
	return _text;
}