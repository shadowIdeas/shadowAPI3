#include "stdafx.h"
#include "ServerAPIOverlayText.h"
#include "OverlayManager.h"
#include "OverlayText.h"

SerializeFunction(ServerAPIOverlayText::Create)
{
	auto text = OverlayManager::GetInstance().CreateElement<OverlayText>(clientId);
	out.WriteInteger(text->GetId());
}

SerializeFunction(ServerAPIOverlayText::Delete)
{
	int id = in.ReadInteger();
	OverlayManager::GetInstance().RemoveElement(clientId, id);
}

SerializeFunction(ServerAPIOverlayText::SetColor)
{
	int id = in.ReadInteger();
	int color = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetColor(color);
}

SerializeFunction(ServerAPIOverlayText::SetX)
{
	int id = in.ReadInteger();
	int x = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetX(x);
}

SerializeFunction(ServerAPIOverlayText::SetY)
{
	int id = in.ReadInteger();
	int y = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetY(y);
}

SerializeFunction(ServerAPIOverlayText::SetMaxWidth)
{
	int id = in.ReadInteger();
	int maxWidth = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetMaxWidth(maxWidth);
}

SerializeFunction(ServerAPIOverlayText::SetMaxHeight)
{
	int id = in.ReadInteger();
	int maxHeight = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetMaxHeight(maxHeight);
}

SerializeFunction(ServerAPIOverlayText::SetActive)
{
	int id = in.ReadInteger();
	bool active = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetActive(active);
}

SerializeFunction(ServerAPIOverlayText::SetText)
{
	int id = in.ReadInteger();
	std::wstring text = in.ReadString();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetText(text);
}

SerializeFunction(ServerAPIOverlayText::SetSize)
{
	int id = in.ReadInteger();
	int size = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetSize(size);
}

SerializeFunction(ServerAPIOverlayText::SetUseMaxWidth)
{
	int id = in.ReadInteger();
	bool useMaxWidth = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetUseMaxWidth(useMaxWidth);
}

SerializeFunction(ServerAPIOverlayText::SetUseMaxHeight)
{
	int id = in.ReadInteger();
	bool useMaxHeight = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);
	if (element)
		element->SetUseMaxHeight(useMaxHeight);
}

SerializeFunction(ServerAPIOverlayText::GetExtent)
{
	int id = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayText>(clientId, id);

	int width = 0;
	int height = 0;
	if (element)
		element->GetTextExtent(width, height);

	out.WriteInteger(width);
	out.WriteInteger(height);
}