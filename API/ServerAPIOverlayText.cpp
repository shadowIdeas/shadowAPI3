#include "stdafx.h"
#include "ServerAPIOverlayText.h"
#include "OverlayManager.h"
#include "OverlayText.h"

void ServerAPIOverlayText::Create(SerializeableQueue & in, SerializeableQueue & out)
{
	auto text = OverlayManager::GetInstance().CreateElement<OverlayText>();
	out.WriteInteger(text->GetId());
}

void ServerAPIOverlayText::Delete(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	OverlayManager::GetInstance().RemoveElement(id);
}

void ServerAPIOverlayText::SetColor(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int color = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetColor(color);
}

void ServerAPIOverlayText::SetX(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int x = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetX(x);
}

void ServerAPIOverlayText::SetY(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int y = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetY(y);
}

void ServerAPIOverlayText::SetText(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	std::wstring text = in.ReadString();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetText(text);
}

void ServerAPIOverlayText::SetSize(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int size = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetSize(size);
}

void ServerAPIOverlayText::GetExtent(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);

	int width = 0;
	int height = 0;
	if (element)
		element->GetTextExtent(width, height);

	out.WriteInteger(width);
	out.WriteInteger(height);
}