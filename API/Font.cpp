#define STRICT

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <d3dx9.h>
#include "Font.h"

#define SAFE_RELEASE( p ) if( p ){ p->Release(); p = NULL; }

//-----------------------------------------------------------------------------
// Custom vertex types for rendering text
//-----------------------------------------------------------------------------
#define MAX_NUM_VERTICES 50*6

struct FONT2DVERTEX { D3DXVECTOR4 p;   DWORD color;     FLOAT tu, tv; };
struct FONT3DVERTEX { D3DXVECTOR3 p;   D3DXVECTOR3 n;   FLOAT tu, tv; };

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define D3DFVF_FONT3DVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

inline FONT2DVERTEX InitFont2DVertex(const D3DXVECTOR4& p, D3DCOLOR color,
	FLOAT tu, FLOAT tv)
{
	FONT2DVERTEX v;   v.p = p;   v.color = color;   v.tu = tu;   v.tv = tv;
	return v;
}

inline FONT3DVERTEX InitFont3DVertex(const D3DXVECTOR3& p, const D3DXVECTOR3& n,
	FLOAT tu, FLOAT tv)
{
	FONT3DVERTEX v;   v.p = p;   v.n = n;   v.tu = tu;   v.tv = tv;
	return v;
}

std::vector<std::shared_ptr<SharedFont>> Font::sharedFonts = std::vector<std::shared_ptr<SharedFont>>();

std::shared_ptr<SharedFont> Font::GetFont(const std::wstring & fontName, DWORD dwHeight, DWORD dwFlags)
{
	std::shared_ptr<SharedFont> font;
	for (size_t i = 0; i < sharedFonts.size(); i++)
	{
		auto tempFont = sharedFonts.at(i);

		// Check for existing font
		if (tempFont != nullptr && tempFont->Compare(fontName, dwHeight, dwFlags))
		{
			font = tempFont;
			break;
		}
	}

	// Create new font
	if (font == nullptr)
	{
		font = std::make_shared<SharedFont>(fontName, dwHeight, dwFlags);
		sharedFonts.push_back(font);
	}

	font->AddReference();

	return font;
}

void Font::ReleaseFont(std::shared_ptr<SharedFont> font)
{
	for (size_t i = 0; i < sharedFonts.size(); i++)
	{
		auto tempFont = sharedFonts.at(i);

		if (font == tempFont)
		{
			if (font->RemoveReference())
				sharedFonts.erase(sharedFonts.begin() + i);

			break;
		}
	}
}

//-----------------------------------------------------------------------------
// Name: Font()
// Desc: Font class constructor
//-----------------------------------------------------------------------------
Font::Font(const std::wstring &fontName, DWORD dwHeight, DWORD dwFlags)
{
	m_pd3dDevice = nullptr;
	m_pVB = NULL;

	m_pStateBlockSaved = NULL;
	m_pStateBlockDrawText = NULL;

	m_font = GetFont(fontName, dwHeight, dwFlags);
	m_dwFlags = dwFlags;

	_scrollY = 0.0f;
}

Font::~Font()
{
	InvalidateDeviceObjects();
	DeleteDeviceObjects();
}

HRESULT Font::InitDeviceObjects(LPDIRECT3DDEVICE9 pd3dDevice)
{
	// Keep a local copy of the device
	m_pd3dDevice = pd3dDevice;
	if (m_font->GetCharacterTexture(m_pd3dDevice, L' ') == nullptr)
		return E_FAIL;

	return S_OK;
}

HRESULT Font::RestoreDeviceObjects()
{
	HRESULT hr;

	int vertexSize = max(sizeof(FONT2DVERTEX), sizeof(FONT3DVERTEX));
	if (FAILED(hr = m_pd3dDevice->CreateVertexBuffer(MAX_NUM_VERTICES * vertexSize,
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return hr;
	}

	for (UINT which = 0; which < 2; which++)
	{
		m_pd3dDevice->BeginStateBlock();

		if (D3DFONT_ZENABLE & m_dwFlags)
			m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		else
			m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		m_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		m_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_CLIPPING, TRUE);
		m_pd3dDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
		m_pd3dDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		m_pd3dDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
			D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
			D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
		m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		m_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

		if (which == 0)
			m_pd3dDevice->EndStateBlock(&m_pStateBlockSaved);
		else
			m_pd3dDevice->EndStateBlock(&m_pStateBlockDrawText);
	}

	return S_OK;
}

HRESULT Font::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pStateBlockSaved);
	SAFE_RELEASE(m_pStateBlockDrawText);

	return S_OK;
}

HRESULT Font::DeleteDeviceObjects()
{
	if (m_font)
	{
		ReleaseFont(m_font);
		m_font = nullptr;
	}

	m_pd3dDevice = nullptr;

	return S_OK;
}

HRESULT Font::GetTextExtent(const WCHAR* strText, SIZE* pSize)
{
	if (m_pd3dDevice == NULL || NULL == strText || NULL == pSize || m_font == nullptr)
		return E_FAIL;

	auto spaceSize = m_font->GetCharacterSize(m_pd3dDevice, L' ');

	float rowWidth = 0.0f;
	float rowHeight = (float)spaceSize.cy;
	float width = 0.0f;
	float height = rowHeight;

	auto stringLength = lstrlenW(strText);

	for (int i = 0; i < stringLength; i++)
	{
		wchar_t c = strText[i];

		if (c == L'{')
		{
			int endIndex = 0;
			bool valid = true;
			std::wstring numericString = L"";
			for (int j = i + 1; j < stringLength; j++)
			{
				wchar_t ch = strText[j];
				ch = towupper(ch);

				if (ch == '}')
				{
					endIndex = j;
					break;
				}

				bool numeric = (ch >= L'0' && ch <= L'9') || (ch >= L'A' && ch <= L'F');
				if (!numeric)
				{
					valid = false;
					break;
				}
				else
				{
					numericString += ch;
					if (numericString.size() > 8)
					{
						valid = false;
						break;
					}
				}
			}

			if (endIndex > 0 && valid)
			{
				i = endIndex;
				continue;
			}
		}

		if (c == '\n')
		{
			rowWidth = 0.0f;
			height += rowHeight;
			continue;
		}

		if (c < 0 || c > USHRT_MAX)
			continue;

		auto characterTexture = m_font->GetCharacterTexture(m_pd3dDevice, c);
		if (characterTexture == nullptr)
			return E_FAIL;

		auto characterSize = m_font->GetCharacterSize(m_pd3dDevice, c);

		rowWidth += characterSize.cx;

		if (rowWidth > width)
			width = rowWidth;
	}

	pSize->cx = (int)width;
	pSize->cy = (int)height;

	return S_OK;
}

void Font::DrawTextProxy(float x, float y, DWORD color, const std::wstring & text, bool useMaxWidth, bool useMaxHeight, int maxWidth, int maxHeight)
{
	// Disable scissor, just draw normal
	if (!useMaxWidth && !useMaxHeight)
	{
		DrawTextInternal(x + 1, y, 0xFF000000, text.c_str());
		DrawTextInternal(x - 1, y, 0xFF000000, text.c_str());
		DrawTextInternal(x, y + 1, 0xFF000000, text.c_str());
		DrawTextInternal(x, y - 1, 0xFF000000, text.c_str());
		DrawTextInternal(x, y, color, text.c_str());
		return;
	}

	if (useMaxWidth || useMaxHeight)
	{
		auto extent = GetTextExtent(text, useMaxWidth, useMaxHeight, maxWidth, maxHeight);
		if (useMaxWidth && !useMaxHeight || (useMaxHeight && extent.cy <= maxHeight))
		{
			DrawTextInternal(x + 1, y, 0xFF000000, text.c_str(), { (int)x, 0, (int)x + maxWidth, 0 });
			DrawTextInternal(x - 1, y, 0xFF000000, text.c_str(), { (int)x, 0, (int)x + maxWidth, 0 });
			DrawTextInternal(x, y + 1, 0xFF000000, text.c_str(), { (int)x, 0, (int)x + maxWidth, 0 });
			DrawTextInternal(x, y - 1, 0xFF000000, text.c_str(), { (int)x, 0, (int)x + maxWidth, 0 });
			DrawTextInternal(x, y, color, text.c_str(), { (int)x, 0, (int)x + maxWidth, 0 });
		}
		else if (useMaxHeight)
		{
			RECT rect = {};

			if (useMaxWidth)
			{
				rect.left = (int)x;
				rect.right = (int)x + extent.cx;
			}

			rect.top = (int)y;
			rect.bottom = (int)y + maxHeight;

			auto spaceSize = m_font->GetCharacterSize(m_pd3dDevice, L' ');
			auto padding = extent.cy + (spaceSize.cy * 2);

			DrawTextInternal(x + 1, y - _scrollY, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x - 1, y - _scrollY, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y - _scrollY + 1, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y - _scrollY - 1, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y - _scrollY, color, text.c_str(), rect);

			DrawTextInternal(x + 1, y + padding - _scrollY, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x - 1, y + padding - _scrollY, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y + padding - _scrollY + 1, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y + padding - _scrollY - 1, 0xFF000000, text.c_str(), rect);
			DrawTextInternal(x, y + padding - _scrollY, color, text.c_str(), rect);

			if (_scrollY >= padding)
				_scrollY = 0.0f;

			_scrollY += 0.5f;
		}
	}
}

SIZE Font::GetTextExtent(const std::wstring & text, bool useMaxWidth, bool useMaxHeight, int maxWidth, int maxHeight)
{
	SIZE size = { };

	auto spaceSize = m_font->GetCharacterSize(m_pd3dDevice, L' ');
	auto stringLength = text.length();

	float rowWidth = 0.0f;
	float rowHeight = (float)spaceSize.cy;
	float width = 0.0f;
	float height = rowHeight;

	for (int i = 0; i < stringLength; i++)
	{
		wchar_t c = text[i];

		if (c == L'{')
		{
			int endIndex = 0;
			bool valid = true;
			std::wstring numericString = L"";
			for (int j = i + 1; j < stringLength; j++)
			{
				wchar_t ch = text[j];
				ch = towupper(ch);

				if (ch == '}')
				{
					endIndex = j;
					break;
				}

				bool numeric = (ch >= L'0' && ch <= L'9') || (ch >= L'A' && ch <= L'F');
				if (!numeric)
				{
					valid = false;
					break;
				}
				else
				{
					numericString += ch;
					if (numericString.size() > 8)
					{
						valid = false;
						break;
					}
				}
			}

			if (endIndex > 0 && valid)
			{
				i = endIndex;
				continue;
			}
		}

		if (c == '\n')
		{
			rowWidth = 0.0f;
			height += rowHeight;
			continue;
		}
		if (useMaxWidth && c == L' ')
		{
			if (rowWidth + spaceSize.cx > maxWidth)
			{
				rowWidth = 0.0f;
				height += rowHeight;
				continue;
			}
		}

		if (c < 0 || c > USHRT_MAX)
			continue;

		auto characterTexture = m_font->GetCharacterTexture(m_pd3dDevice, c);
		auto characterSize = m_font->GetCharacterSize(m_pd3dDevice, c);

		rowWidth += characterSize.cx;

		if (rowWidth > width)
			width = rowWidth;
	}

	size.cx = (int)width;
	size.cy = (int)height;
	return size;
}

HRESULT Font::DrawTextInternal(float x, float y, DWORD color, const WCHAR* text, RECT scissorRect, DWORD flags)
{
	if (m_pd3dDevice == 0 || text == 0 || m_font == nullptr)
		return E_FAIL;

	int maxWidth = scissorRect.right - scissorRect.left;
	int maxHeight = scissorRect.bottom - scissorRect.top;

	bool useMaxWidth = maxWidth != 0;
	bool useMaxHeight = maxHeight != 0;

	// Setup renderstate
	m_pStateBlockSaved->Capture();
	m_pStateBlockDrawText->Apply();
	m_pd3dDevice->SetFVF(D3DFVF_FONT2DVERTEX);
	m_pd3dDevice->SetPixelShader(NULL);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(FONT2DVERTEX));

	if (useMaxHeight)
	{
		m_pd3dDevice->SetScissorRect(&scissorRect);
		m_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	}

	if (flags & D3DFONT_FILTERED)
	{
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}

	// Adjust for character spacing
	auto spaceSize = m_font->GetCharacterSize(m_pd3dDevice, L' ');
	float startX = x;

	// Fill vertex buffer
	FONT2DVERTEX* vertices = NULL;
	int trianglesCount = 0;
	m_pVB->Lock(0, 0, (void**)&vertices, D3DLOCK_DISCARD);

	auto stringLength = lstrlenW(text);
	DWORD customColor = color;

	auto textures = std::vector<LPDIRECT3DTEXTURE9>();

	for (int i = 0; i < stringLength; i++)
	{
		wchar_t c = text[i];

		if (c == L'{')
		{
			int endIndex = 0;
			bool valid = true;
			std::wstring numericString = L"";
			for (int j = i + 1; j < stringLength; j++)
			{
				wchar_t ch = text[j];
				ch = towupper(ch);

				if (ch == '}')
				{
					endIndex = j;
					break;
				}

				bool numeric = (ch >= L'0' && ch <= L'9') || (ch >= L'A' && ch <= L'F');
				if (!numeric)
				{
					valid = false;
					break;
				}
				else
				{
					numericString += ch;
					if (numericString.size() > 8)
					{
						valid = false;
						break;
					}
				}
			}

			if (endIndex > 0 && valid)
			{
				swscanf_s(numericString.data(), L"%X", &customColor);
				customColor |= (color >> 24) << 24;
				i = endIndex;
				continue;
			}
		}

		if (c == '\n')
		{
			x = startX;
			y += spaceSize.cy;
			continue;
		}
		if (useMaxWidth && c == L' ')
		{
			if ((x - startX) + spaceSize.cx > maxWidth)
			{
				x = startX;
				y += spaceSize.cy;
				continue;
			}
		}
		if (c < 0 || c > USHRT_MAX)
			continue;

		auto characterTexture = m_font->GetCharacterTexture(m_pd3dDevice, c);
		if (characterTexture == nullptr)
			return E_FAIL;

		auto characterSize = m_font->GetCharacterSize(m_pd3dDevice, c);

		float w = (float)characterSize.cx;
		float h = (float)characterSize.cy;

		if (c != L' ')
		{
			if (flags & D3DFONT_COLORTABLE)
				color = customColor;

			*vertices++ = InitFont2DVertex(D3DXVECTOR4(x - 0.5f, y - 0.5f, 0.9f, 1.0f), color, 0, 0);
			*vertices++ = InitFont2DVertex(D3DXVECTOR4(x - 0.5f + w, y - 0.5f, 0.9f, 1.0f), color, 1.0, 0.0);
			*vertices++ = InitFont2DVertex(D3DXVECTOR4(x - 0.5f + w, y - 0.5f + h, 0.9f, 1.0f), color, 1.0, 1.0);
			*vertices++ = InitFont2DVertex(D3DXVECTOR4(x - 0.5f, y - 0.5f + h, 0.9f, 1.0f), color, 0.0, 1.0);
			trianglesCount += 2;

			// Push texture
			textures.push_back(characterTexture);

			// We need to draw the text everytime, because the texture changed
			// Unlock, render, and relock the vertex buffer

			if (trianglesCount * 3 >= MAX_NUM_VERTICES - 6)
			{
				m_pVB->Unlock();

				for (size_t i = 0; i < textures.size(); i++)
				{
					m_pd3dDevice->SetTexture(0, textures[i]);
					m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, i * 4, 2);
					m_pd3dDevice->SetTexture(0, NULL);
				}

				vertices = NULL;
				m_pVB->Lock(0, 0, (void**)&vertices, D3DLOCK_DISCARD);

				textures.clear();
				trianglesCount = 0L;
			}
		}

		x += w;
	}

	// Unlock and render the vertex buffer
	m_pVB->Unlock();
	if (trianglesCount > 0)
	{
		for (size_t i = 0; i < textures.size(); i++)
		{
			m_pd3dDevice->SetTexture(0, textures[i]);
			m_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, i * 4, 2);
			m_pd3dDevice->SetTexture(0, NULL);
		}
	}

	if (useMaxHeight)
		m_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	// Restore the modified renderstates
	m_pStateBlockSaved->Apply();

	return S_OK;
}