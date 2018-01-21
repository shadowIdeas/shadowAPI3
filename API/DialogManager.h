#pragma once
class DialogManager
{
public:
	static DialogManager &GetInstance();

	void StartBlock(int id, const std::wstring &caption);

	bool ShouldBlock(int id, const std::wstring &caption, const std::wstring &text);

	bool HasBlocked();
	const std::wstring &GetCaption();
	const std::wstring &GetText();
private:
	bool _blockActive;
	int _blockId;
	std::wstring _blockCaption;

	std::wstring _caption;
	std::wstring _text;

	DialogManager();
	~DialogManager();
};
