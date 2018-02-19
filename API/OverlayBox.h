#pragma once
#include "OverlayElement.h"

struct Vertex
{
	float x;
	float y;
	float z;
	float w;
	D3DCOLOR color;
};

class OverlayBox : public OverlayElement
{
public:
	OverlayBox(int clientId, int id);
	~OverlayBox();

	void SetWidth(int width);
	void SetHeight(int height);
	void SetColor(unsigned long color);

	virtual void Present(LPDIRECT3DDEVICE9 device) override;
	virtual void Reset(LPDIRECT3DDEVICE9 device) override;
	virtual void OnRemove() override;
private:
	int _width;
	int _height;
	unsigned long _color;
};
