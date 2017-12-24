#include "stdafx.h"
#include "OverlayElement.h"

OverlayElement::OverlayElement(int id)
{
	_id = id;
	_x = 0;
	_y = 0;
	_active = false;
}

OverlayElement::~OverlayElement()
{
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