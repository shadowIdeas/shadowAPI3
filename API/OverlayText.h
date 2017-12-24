#pragma once
#include <memory>

#include "OverlayElement.h"
#include "Font.h"

class OverlayText : public OverlayElement
{
public:
	OverlayText(int id);
	~OverlayText();

	const std::wstring &GetText();
	void SetText(const std::wstring &text);
	void SetColor(unsigned long color);
	void SetMaxWidth(int maxWidth);
	void SetMaxHeight(int maxHeight);
	void SetSize(int size);
	void SetUseMaxWidth(bool useMaxWidth);
	void SetUseMaxHeight(bool useMaxHeight);
	void GetTextExtent(int &width, int &height);

	virtual void Present(LPDIRECT3DDEVICE9 device) override;
	virtual void Reset(LPDIRECT3DDEVICE9 device) override;
private:
	std::unique_ptr<Font> _font;
	std::wstring _text;
	unsigned long _color;
	int _size;

	bool _useMaxWidth;
	bool _useMaxHeight;
	int _maxWidth;
	int _maxHeight;

	bool _firstDraw;

	void ResetText();
};
