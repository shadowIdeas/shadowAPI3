#include "stdafx.h"
#include "NativeGeneral.h"

int NativeGeneral::GetWeatherId()
{
	return *(WORD*)0xC81320;
}

void NativeGeneral::SetKey(int key, bool pressed)
{
	typedef int(__cdecl *EnableKey)(int*);
	typedef int(__cdecl *DisableKey)(int*);
	static EnableKey enableKey = (EnableKey)0x743DF0;
	static DisableKey disableKey = (EnableKey)0x7443C0;

	if (pressed)
		enableKey(&key);
	else
		disableKey(&key);
}
