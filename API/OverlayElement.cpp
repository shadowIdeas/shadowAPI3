#include "stdafx.h"
#include "OverlayElement.h"

OverlayElement::OverlayElement(int clientId, int id)
{
	_clientId = clientId;
	_id = id;
	_x = 0;
	_y = 0;
	_active = false;
	_removed = false;
}

OverlayElement::~OverlayElement()
{
}

int OverlayElement::GetClientId()
{
	return _clientId;
}

int OverlayElement::GetId()
{
	return _id;
}

bool OverlayElement::GetActive()
{
	return _active;
}

int OverlayElement::GetX()
{
	return _x;
}

int OverlayElement::GetY()
{
	return _y;
}

void OverlayElement::SetActive(bool active)
{
	_active = active;
}

void OverlayElement::SetX(int x)
{
	_x = x;
}

void OverlayElement::SetY(int y)
{
	_y = y;
}

bool OverlayElement::IsRemoved()
{
	return _removed;
}

void OverlayElement::MarkAsRemoved()
{
	_removed = true;
}
