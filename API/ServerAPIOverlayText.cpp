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

void ServerAPIOverlayText::SetMaxWidth(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int maxWidth = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetMaxWidth(maxWidth);
}

void ServerAPIOverlayText::SetMaxHeight(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int maxHeight = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetMaxHeight(maxHeight);
}

void ServerAPIOverlayText::SetActive(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	bool active = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetActive(active);
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

void ServerAPIOverlayText::SetUseMaxWidth(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	bool useMaxWidth = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetUseMaxWidth(useMaxWidth);
}

void ServerAPIOverlayText::SetUseMaxHeight(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	bool useMaxHeight = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(id);
	if (element)
		element->SetUseMaxHeight(useMaxHeight);
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