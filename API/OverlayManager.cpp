#include "stdafx.h"
#include "OverlayManager.h"
#include "Utils.h"

DWORD _sampPresent;
DWORD _sampReset;

__declspec(naked) void PresentHook()
{
	__asm pushad;
	__asm pushfd;

	OverlayManager::GetInstance().PresentProxy();

	__asm popfd;
	__asm popad;

	__asm push edx;
	__asm mov edx, [ebp + 0x14];
	__asm push edx;

	__asm jmp[_sampPresent];
}

__declspec(naked) void ResetHook()
{
	__asm pushad;
	__asm pushfd;

	OverlayManager::GetInstance().ResetProxy();

	__asm popfd;
	__asm popad;

	__asm mov ecx, [eax];
	__asm push edx;
	__asm push eax;
	__asm call dword ptr[ecx + 0x40];

	__asm jmp[_sampReset];
}

OverlayManager::OverlayManager()
{
	_idCounter = 0;
	HMODULE module = GetModuleHandle(L"samp.dll");

	_sampPresent = Utils::DetourNaked(((DWORD)module + 0x7166D), (DWORD)&PresentHook, 5);
	_sampReset = Utils::DetourNaked(((DWORD)module + 0x6FFEF), (DWORD)&ResetHook, 7);
}

OverlayManager::~OverlayManager()
{
}

OverlayManager & OverlayManager::GetInstance()
{
	static OverlayManager instance;
	return instance;
}

void OverlayManager::RemoveElement(int clientId, int id)
{
	std::lock_guard<std::mutex> guard(_elementMutex);
	for (size_t i = 0; i < _elements.size(); i++)
	{
		auto element = _elements[i];
		if (element->GetId() == id && element->GetClientId() == clientId)
		{
			_elements[i]->MarkAsRemoved();
			break;
		}
	}
}

void OverlayManager::Cleanup(int clientId)
{
	std::lock_guard<std::mutex> guard(_elementMutex);
	for (size_t i = 0; i < _elements.size(); i++)
	{
		if(_elements[i]->GetClientId() == clientId)
			_elements[i]->MarkAsRemoved();
	}
}

void OverlayManager::PresentProxy()
{
	std::lock_guard<std::mutex> guard(_elementMutex);
	auto device = (LPDIRECT3DDEVICE9)(*(DWORD*)(0xC97C28));

	for (auto iterator = _elements.begin(); iterator != _elements.end();)
	{
		auto element = iterator->get();

		if (!element)
			continue;

		if (element->IsRemoved())
		{
			element->OnRemove();
			iterator = _elements.erase(iterator);
			continue;
		}


		if (element->GetActive())
			element->Present(device);

		iterator++;
	}
}

void OverlayManager::ResetProxy()
{
	std::lock_guard<std::mutex> guard(_elementMutex);
	auto device = (LPDIRECT3DDEVICE9)(*(DWORD*)(0xC97C28));

	for (size_t i = 0; i < _elements.size(); i++)
	{
		auto element = _elements[i];
		if (element)
			element->Reset(device);
	}
}