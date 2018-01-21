#include "stdafx.h"
#include "NativeGeneral.h"

int NativeGeneral::GetWeatherId()
{
	return *(WORD*)0xC81320;
}
