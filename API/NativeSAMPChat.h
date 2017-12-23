#pragma once
#include "SerializeableQueue.h"

static class NativeSAMPChat
{
public:
	static void Send(const std::wstring &text);
	static void AddMessage(const std::wstring &text, int color = 0xFFFFFF);

	static std::wstring GetText();
	static void SetText(const std::wstring &text);

	static std::wstring GetBufferMessage(int index);
	static void AddBufferMessage(const std::wstring &text);

	static void SetCursorPosition(int index);
	static void SetCursorPosition(int indexStart, int indexEnd);

	static void Toggle(bool state);
	static void Clear();

	static bool IsOpen();
};
