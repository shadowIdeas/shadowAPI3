#pragma once
#include "PacketTypeIdentifier.h"

struct PacketTypeData
{
	PacketTypeIdentifier identifier;
	UINT size;

	std::vector<BYTE> data;
};