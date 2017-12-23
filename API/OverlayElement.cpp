#include "stdafx.h"
#include "OverlayElement.h"

OverlayElement::OverlayElement(int id)
{
	_id = id;
	_x = 0;
	_y = 0;
}

OverlayElement::~OverlayElement()
{
}

int OverlayElement::GetId()
{
	return _id;
}

int OverlayElement::GetX()
{
	return _x;
}

int OverlayElement::GetY()
{
	return _y;
}

void OverlayElement::SetX(int x)
{
	_x = x;
}

void OverlayElement::SetY(int y)
{
	_y = y;
}