#pragma once
static class NativeSAMPDialog
{
public:
	static std::wstring GetText();
	static void SetText(const std::wstring &text);

	static void SetCursorPosition(int index);
	static void SetCursorPosition(int indexStart, int indexEnd);

	static int GetId();
	static int GetStringCount();
	static std::wstring GetStringByIndex(int index);

	static void Clear();
	static void Close(int reason);
	static void SelectIndex(int index);

	static bool IsOpen();

	static std::wstring BlockGetCaption();
	static std::wstring BlockGetText();

	static void Block(int id, const std::wstring &text);
	static bool BlockHasBlockedDialog();
	static bool BlockHasNeedBlocking();
};
