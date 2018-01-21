#include "stdafx.h"
#include "OverlayBox.h"

OverlayBox::OverlayBox(int id)
	: OverlayElement(id)
{
	_width = 0;
	_height = 0;
	_color = 0xFFFFFFFF;
}

OverlayBox::~OverlayBox()
{
}

void OverlayBox::SetWidth(int width)
{
	_width = width;
}

void OverlayBox::SetHeight(int height)
{
	_height = height;
}

void OverlayBox::SetColor(unsigned long color)
{
	_color = color;
}

void OverlayBox::Present(LPDIRECT3DDEVICE9 device)
{
	DWORD fvf;
	LPDIRECT3DPIXELSHADER9 pixelShader;
	LPDIRECT3DBASETEXTURE9 texture;

	device->GetFVF(&fvf);
	device->GetPixelShader(&pixelShader);
	device->GetTexture(0, &texture);

	device->SetPixelShader(NULL);
	device->SetTexture(0, NULL);
	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

	Vertex vertices[4] = {};
	vertices[0].color = _color;
	vertices[1].color = _color;
	vertices[2].color = _color;
	vertices[3].color = _color;

	vertices[0].z = 0.0f;
	vertices[1].z = 0.0f;
	vertices[2].z = 0.0f;
	vertices[3].z = 0.0f;

	vertices[0].w = 0.0f;
	vertices[1].w = 0.0f;
	vertices[2].w = 0.0f;
	vertices[3].w = 0.0f;

	vertices[0].x = GetX();
	vertices[2].x = GetX();

	vertices[0].y = GetY();
	vertices[1].y = GetY();

	vertices[1].x = GetX() + _width;
	vertices[3].x = GetX() + _width;

	vertices[2].y = GetY() + _height;
	vertices[3].y = GetY() + _height;

	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex));

	device->SetPixelShader(pixelShader);
	device->SetTexture(0, texture);
	device->SetFVF(fvf);
}

void OverlayBox::Reset(LPDIRECT3DDEVICE9 device)
{
}

void OverlayBox::OnRemove()
{
}
