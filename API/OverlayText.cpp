#include "stdafx.h"
#include "OverlayText.h"

#include "NativeSAMPChat.h"

OverlayText::OverlayText(int clientId, int id)
	: OverlayElement(clientId, id)
{
	_firstDraw = true;
	_fontChange = false;
	_color = 0xFFFFFFFF;
	_size = 12;

	_useMaxWidth = false;
	_useMaxHeight = false;
	_maxWidth = 0;
	_maxHeight = 0;
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

void OverlayText::SetMaxWidth(int maxWidth)
{
	_maxWidth = maxWidth;
}

void OverlayText::SetMaxHeight(int maxHeight)
{
	_maxHeight = maxHeight;
}

void OverlayText::SetSize(int size)
{
	if (_size == size)
		return;

	_size = size;
	_fontChange = true;
}

void OverlayText::SetUseMaxWidth(bool useMaxWidth)
{
	_useMaxWidth = useMaxWidth;
}

void OverlayText::SetUseMaxHeight(bool useMaxHeight)
{
	_useMaxHeight = useMaxHeight;
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
	if (_firstDraw || _fontChange)
	{
		_font = std::make_unique<Font>(L"Arial", _size, D3DFONT_FILTERED | D3DFONT_BOLD);
		_font->InitDeviceObjects(device);
		_font->RestoreDeviceObjects();

		_firstDraw = false;
		_fontChange = false;
	}

	if (_font)
	{
		_font->DrawTextProxy(GetX(), GetY(), _color, _text, _useMaxWidth, _useMaxHeight, _maxWidth, _maxHeight);
	}
}

void OverlayText::Reset(LPDIRECT3DDEVICE9 device)
{
	ResetText();
	_firstDraw = true;
}

void OverlayText::ResetText()
{
	_font.reset();
}

void OverlayText::OnRemove()
{
	ResetText();
}
