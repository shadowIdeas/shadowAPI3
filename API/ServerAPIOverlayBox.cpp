#include "stdafx.h"
#include "ServerAPIOverlayBox.h"
#include "OverlayManager.h"
#include "OverlayBox.h"

SerializeFunction(ServerAPIOverlayBox::Create)
{
	auto box = OverlayManager::GetInstance().CreateElement<OverlayBox>(clientId);
	out.WriteInteger(box->GetId());
}

SerializeFunction(ServerAPIOverlayBox::Delete)
{
	int id = in.ReadInteger();
	OverlayManager::GetInstance().RemoveElement(clientId, id);
}

SerializeFunction(ServerAPIOverlayBox::SetColor)
{
	int id = in.ReadInteger();
	int color = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetColor(color);
}

SerializeFunction(ServerAPIOverlayBox::SetX)
{
	int id = in.ReadInteger();
	int x = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetX(x);
}

SerializeFunction(ServerAPIOverlayBox::SetY)
{
	int id = in.ReadInteger();
	int y = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetY(y);
}

SerializeFunction(ServerAPIOverlayBox::SetWidth)
{
	int id = in.ReadInteger();
	int width = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetWidth(width);
}

SerializeFunction(ServerAPIOverlayBox::SetHeight)
{
	int id = in.ReadInteger();
	int height = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetHeight(height);
}

SerializeFunction(ServerAPIOverlayBox::SetActive)
{
	int id = in.ReadInteger();
	bool active = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(clientId, id);
	if (element)
		element->SetActive(active);
}