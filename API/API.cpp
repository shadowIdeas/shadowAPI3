// API.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include "API.h"
#include "SerializeableQueue.h"

DllPublic int API::Initialize(const wchar_t * path, const wchar_t * file)
{
	return 0;
}

DllPublic int API::ResetInitialize()
{
}

DllPublic int API::Other::GetWeatherID()
{
	return 0;
}

DllPublic int API::Other::Useless(int useless)
{
	SerializeableQueue in;
	int integerIn = useless;
	float floatIn = 4.2f;
	bool booleanIn = true;
	std::wstring stringIn = L"Hello World! It's me :(";
	in.WriteInteger(integerIn);
	in.WriteFloat(floatIn);
	in.WriteBoolean(booleanIn);
	in.WriteString(stringIn);

	SerializeableQueue out(in);
	int integerOut = out.ReadInteger();
	float floatOut = out.ReadFloat();
	bool booleanOut = out.ReadBoolean();
	std::wstring stringOut = out.ReadString();

	return useless;
}

DllPublic int API::Other::Useless1()
{
	return 0;
}

DllPublic int API::Overlay::Box::Create()
{
	return 0;
}

DllPublic void API::Overlay::Box::Delete(int id)
{
}

DllPublic void API::Overlay::Box::SetColor(int id, unsigned int color)
{
}

DllPublic void API::Overlay::Box::SetX(int id, int x)
{
}

DllPublic void API::Overlay::Box::SetY(int id, int y)
{
}

DllPublic void API::Overlay::Box::SetWidth(int id, int width)
{
}

DllPublic void API::Overlay::Box::SetHeight(int id, int height)
{
}

DllPublic void API::Overlay::Box::SetActive(int id, bool active)
{
}

DllPublic int API::Overlay::Text::Create()
{
	return 0;
}

DllPublic void API::Overlay::Text::Delete(int id)
{
}

DllPublic void API::Overlay::Text::SetColor(int id, unsigned int color)
{
}

DllPublic void API::Overlay::Text::SetX(int id, int x)
{
}

DllPublic void API::Overlay::Text::SetY(int id, int y)
{
}

DllPublic void API::Overlay::Text::SetWidth(int id, int width)
{
}

DllPublic void API::Overlay::Text::SetHeight(int id, int height)
{
}

DllPublic void API::Overlay::Text::SetActive(int id, bool active)
{
}

DllPublic void API::Overlay::Text::SetText(int id, const wchar_t * text)
{
}

DllPublic void API::Overlay::Text::SetSize(int id, int size)
{
}

DllPublic void API::Overlay::Text::SetUseMaxWidth(int id, int maxWidth)
{
}

DllPublic void API::Overlay::Text::SetUseMaxHeight(int id, int maxHeight)
{
}

DllPublic int API::Overlay::Text::GetTextExtent(int id, int & width, int & height)
{
	return 0;
}