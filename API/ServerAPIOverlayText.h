#pragma once
#include "SerializeableQueue.h"
static class ServerAPIOverlayText
{
public:
	static void Create(SerializeableQueue &in, SerializeableQueue &out);
	static void Delete(SerializeableQueue &in, SerializeableQueue &out);
	static void SetColor(SerializeableQueue &in, SerializeableQueue &out);
	static void SetX(SerializeableQueue &in, SerializeableQueue &out);
	static void SetY(SerializeableQueue &in, SerializeableQueue &out);
	static void SetText(SerializeableQueue &in, SerializeableQueue &out);
	static void SetSize(SerializeableQueue &in, SerializeableQueue &out);
	static void GetExtent(SerializeableQueue &in, SerializeableQueue &out);
};
