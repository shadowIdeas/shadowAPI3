#include "stdafx.h"
#include "ServerAPIOverlayBox.h"
#include "OverlayManager.h"
#include "OverlayBox.h"

void ServerAPIOverlayBox::Create(SerializeableQueue & in, SerializeableQueue & out)
{
	auto box = OverlayManager::GetInstance().CreateElement<OverlayBox>();
	out.WriteInteger(box->GetId());
}

void ServerAPIOverlayBox::Delete(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	OverlayManager::GetInstance().RemoveElement(id);
}

void ServerAPIOverlayBox::SetColor(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int color = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetColor(color);
}

void ServerAPIOverlayBox::SetX(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int x = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetX(x);
}

void ServerAPIOverlayBox::SetY(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int y = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetY(y);
}

void ServerAPIOverlayBox::SetWidth(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int width = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetWidth(width);
}

void ServerAPIOverlayBox::SetHeight(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	int height = in.ReadInteger();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetHeight(height);
}

void ServerAPIOverlayBox::SetActive(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	bool active = in.ReadBoolean();
	auto element = OverlayManager::GetInstance().GetElementById<OverlayBox>(id);
	if (element)
		element->SetActive(active);
}