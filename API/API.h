#pragma once
#include "Client.h"

#define DllPublic   __declspec( dllexport )

static Client g_client;

namespace API
{
	DllPublic int Initialize(const wchar_t *path, const wchar_t *file);
	DllPublic int ResetInitialize();

	namespace Other
	{
		DllPublic int GetWeatherID();
		DllPublic int Useless(int useless);
		DllPublic int Useless1();
	}

	namespace SAMP
	{
	}

	namespace Overlay
	{
		namespace Box
		{
			DllPublic int Create();
			DllPublic void Delete(int id);
			DllPublic void SetColor(int id, unsigned int color);
			DllPublic void SetX(int id, int x);
			DllPublic void SetY(int id, int y);
			DllPublic void SetWidth(int id, int width);
			DllPublic void SetHeight(int id, int height);
			DllPublic void SetActive(int id, bool active);
		}

		namespace Text
		{
			DllPublic int Create();
			DllPublic void Delete(int id);
			DllPublic void SetColor(int id, unsigned int color);
			DllPublic void SetX(int id, int x);
			DllPublic void SetY(int id, int y);
			DllPublic void SetWidth(int id, int width);
			DllPublic void SetHeight(int id, int height);
			DllPublic void SetActive(int id, bool active);

			DllPublic void SetText(int id, const wchar_t *text);
			DllPublic void SetSize(int id, int size);
			DllPublic void SetUseMaxWidth(int id, int maxWidth);
			DllPublic void SetUseMaxHeight(int id, int maxHeight);
			DllPublic int GetTextExtent(int id, int &width, int &height);
		}
	}

	namespace Player
	{
	}

	namespace Vehicle
	{
	}
}