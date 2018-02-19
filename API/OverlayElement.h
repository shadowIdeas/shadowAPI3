#pragma once
#include <d3d9.h>

class OverlayElement
{
public:
	OverlayElement(int clientId, int id);
	~OverlayElement();

	virtual void Present(LPDIRECT3DDEVICE9 device) = 0;
	virtual void Reset(LPDIRECT3DDEVICE9 device) = 0;

	int GetClientId();
	int GetId();
	bool GetActive();
	int GetX();
	int GetY();
	void SetActive(bool active);
	void SetX(int x);
	void SetY(int y);

	bool IsRemoved();
	void MarkAsRemoved();
	virtual void OnRemove() = 0;
private:
	int _clientId;
	int _id;
	bool _active;
	int _x;
	int _y;

	bool _removed;
};
