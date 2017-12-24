#pragma once
#include "SerializeableQueue.h"
static class ServerAPIOverlayBox
{
public:
	static void Create(SerializeableQueue &in, SerializeableQueue &out);
	static void Delete(SerializeableQueue &in, SerializeableQueue &out);
	static void SetColor(SerializeableQueue &in, SerializeableQueue &out);
	static void SetX(SerializeableQueue &in, SerializeableQueue &out);
	static void SetY(SerializeableQueue &in, SerializeableQueue &out);
	static void SetWidth(SerializeableQueue &in, SerializeableQueue &out);
	static void SetHeight(SerializeableQueue &in, SerializeableQueue &out);
	static void SetActive(SerializeableQueue &in, SerializeableQueue &out);
};
