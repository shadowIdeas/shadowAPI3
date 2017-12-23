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
	void SetSize(int size);
	void GetTextExtent(int &width, int &height);

	virtual void Present(LPDIRECT3DDEVICE9 device) override;
	virtual void Reset(LPDIRECT3DDEVICE9 device) override;
private:
	std::unique_ptr<Font> _font;
	std::wstring _text;
	unsigned long _color;
	int _size;

	bool _firstDraw;

	void ResetText();
};
