#pragma once
#include <d3d9.h>

class OverlayElement
{
public:
	OverlayElement(int id);
	~OverlayElement();

	virtual void Present(LPDIRECT3DDEVICE9 device) = 0;
	virtual void Reset(LPDIRECT3DDEVICE9 device) = 0;

	int GetId();
	bool GetActive();
	int GetX();
	int GetY();
	void SetActive(bool active);
	void SetX(int x);
	void SetY(int y);
private:
	int _id;
	bool _active;
	int _x;
	int _y;
};
