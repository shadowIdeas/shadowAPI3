#pragma once
#include "Client.h"

#define DllPublic   __declspec( dllexport )

static std::shared_ptr<Client> g_client;

namespace API
{
	DllPublic int Initialize(const wchar_t *path, const wchar_t *file);
	DllPublic void ResetInitialize();

	namespace Other
	{
		DllPublic int GetWeatherID();
		DllPublic int Useless(int useless);
		DllPublic int Useless1();
	}

	namespace SAMP
	{
		namespace Chat
		{
			DllPublic void Send(const wchar_t *message);
			DllPublic void AddMessage(const wchar_t *message);
			DllPublic void AddMessage(const wchar_t *message, unsigned long color);

			DllPublic void GetText(wchar_t *text, int length);
			DllPublic void SetText(const wchar_t *text);

			DllPublic void GetBufferMessage(int index, wchar_t *message, int length);
			DllPublic void AddBufferMessage(const wchar_t *message);

			DllPublic void SetCursorPosition(int index);
			DllPublic void SetCursorPosition(int indexStart, int indexEnd);

			DllPublic void Toggle(bool state);
			DllPublic void Clear();

			DllPublic bool IsOpen();
		}

		namespace Dialog
		{
			DllPublic void GetText(wchar_t *text, int length);
			DllPublic void SetText(const wchar_t *text);
			DllPublic void ClearText();

			DllPublic void SetCursorPosition(int index);
			DllPublic void SetCursorPosition(int indexStart, int indexEnd);

			DllPublic int GetID();
			DllPublic int GetStringCount();
			DllPublic void GetStringByIndex(int index, wchar_t *text, int length);

			DllPublic bool IsOpen();
			DllPublic void Close(int reason);
			DllPublic void SelectIndex(int index);

			DllPublic void BlockGetCaption(wchar_t *caption, int length);
			DllPublic void BlockGetText(wchar_t *text, int length);

			DllPublic void Block(int id, const wchar_t *text);
			DllPublic bool BlockHasBlockedDialog();
			DllPublic bool BlockHasNeedBlocking();
		}

		namespace Player
		{
			DllPublic void GetLocalName(wchar_t *name, int length);
			DllPublic int GetLocalId();

			DllPublic void GetNameById(int id, wchar_t *name, int length);
			DllPublic int GetIdByName(const wchar_t *name);
			DllPublic void GetFullName(const wchar_t *name, wchar_t *fullName, int length);
		}

		namespace Vehicle
		{
			DllPublic void GetNumberplate(wchar_t *numberplate, int length);
			DllPublic void ToggleSiren(bool state);
		}
	}

	namespace Overlay
	{
		namespace Box
		{
			DllPublic int Create();
			DllPublic void Delete(int id);
			DllPublic void SetColor(int id, unsigned long color);
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
			DllPublic void SetColor(int id, unsigned long color);
			DllPublic void SetX(int id, int x);
			DllPublic void SetY(int id, int y);
			DllPublic void SetMaxWidth(int id, int maxWidth);
			DllPublic void SetMaxHeight(int id, int maxHeight);

			DllPublic void SetActive(int id, bool active);

			DllPublic void SetText(int id, const wchar_t *text);
			DllPublic void SetSize(int id, int size);
			DllPublic void SetUseMaxWidth(int id, bool state);
			DllPublic void SetUseMaxHeight(int id, bool state);
			DllPublic void GetTextExtent(int id, int &width, int &height);
		}
	}

	namespace Player
	{
		DllPublic int GetHealth();
		DllPublic int GetArmor();
		DllPublic int GetInteriorId();
		DllPublic void GetCity(wchar_t *city, int length);
		DllPublic void GetDistrict(wchar_t *district, int length);
		DllPublic void GetPosition(float &x, float &y, float &z);
		DllPublic float GetYaw();

		DllPublic bool InInterior();
		DllPublic bool InVehicle();
		DllPublic bool IsDriver();
	}

	namespace Vehicle
	{
		DllPublic float GetSpeed();
		DllPublic float GetHealth();
		DllPublic int GetModelID();

		DllPublic bool IsLightActive();
		DllPublic bool IsLocked();
		DllPublic bool IsEngineRunning();

		DllPublic bool UseHorn();
		DllPublic bool UseSiren();
	}
}