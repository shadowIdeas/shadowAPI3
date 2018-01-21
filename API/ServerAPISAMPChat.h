#pragma once
#include "SerializeableQueue.h"

static class ServerAPISAMPChat
{
public:
	static void Send(SerializeableQueue &in, SerializeableQueue &out);
	static void AddMessage1(SerializeableQueue &in, SerializeableQueue &out);
	static void AddMessage2(SerializeableQueue &in, SerializeableQueue &out);

	static void GetText(SerializeableQueue &in, SerializeableQueue &out);
	static void SetText(SerializeableQueue &in, SerializeableQueue &out);

	static void GetBufferMessage(SerializeableQueue &in, SerializeableQueue &out);
	static void AddBufferMessage(SerializeableQueue &in, SerializeableQueue &out);

	static void SetCursorPosition(SerializeableQueue &in, SerializeableQueue &out);
	static void SetCursorPosition2(SerializeableQueue &in, SerializeableQueue &out);

	static void Toggle(SerializeableQueue &in, SerializeableQueue &out);
	static void Clear(SerializeableQueue &in, SerializeableQueue &out);

	static void IsOpen(SerializeableQueue &in, SerializeableQueue &out);
};
