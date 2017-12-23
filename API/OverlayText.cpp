#include "stdafx.h"
#include "OverlayText.h"

#include "NativeSAMPChat.h"

OverlayText::OverlayText(int id)
	: OverlayElement(id)
{
	_firstDraw = true;
	_color = 0xFFFFFFFF;
	_size = 12;
}

OverlayText::~OverlayText()
{
}

const std::wstring & OverlayText::GetText()
{
	return _text;
}

void OverlayText::SetText(const std::wstring & text)
{
	_text = text;
}

void OverlayText::SetColor(unsigned long color)
{
	_color = color;
}

void OverlayText::SetSize(int size)
{
	_size = size;
	ResetText();
}

void OverlayText::GetTextExtent(int & width, int & height)
{
	if (!_font)
		return;

	SIZE size = {};
	_font->GetTextExtent(_text.c_str(), &size);

	width = size.cx;
	height = size.cy;
}

void OverlayText::Present(LPDIRECT3DDEVICE9 device)
{
	if (_firstDraw)
	{
		_font = std::make_unique<Font>(L"Arial", _size, D3DFONT_FILTERED | D3DFONT_BOLD);
		_font->InitDeviceObjects(device);
		_font->RestoreDeviceObjects();

		_firstDraw = false;
	}

	if (_font)
	{
		_font->DrawTextW(GetX() + 1, GetY(), 0xFF000000, _text.c_str());
		_font->DrawTextW(GetX() - 1, GetY(), 0xFF000000, _text.c_str());
		_font->DrawTextW(GetX(), GetY() + 1, 0xFF000000, _text.c_str());
		_font->DrawTextW(GetX(), GetY() - 1, 0xFF000000, _text.c_str());

		_font->DrawTextW(GetX(), GetY(), _color, _text.c_str());
	}
}

void OverlayText::Reset(LPDIRECT3DDEVICE9 device)
{
	ResetText();
}

void OverlayText::ResetText()
{
	_font = nullptr;
	_firstDraw = true;
}