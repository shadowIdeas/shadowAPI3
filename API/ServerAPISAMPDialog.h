#pragma once
#include "SerializeableQueue.h"
static class ServerAPISAMPDialog
{
public:
	static void GetText(SerializeableQueue &in, SerializeableQueue &out);
	static void SetText(SerializeableQueue &in, SerializeableQueue &out);
	static void SetCursorPosition1(SerializeableQueue &in, SerializeableQueue &out);
	static void SetCursorPosition2(SerializeableQueue &in, SerializeableQueue &out);
	static void GetId(SerializeableQueue &in, SerializeableQueue &out);
	static void GetStringCount(SerializeableQueue &in, SerializeableQueue &out);
	static void GetStringByIndex(SerializeableQueue &in, SerializeableQueue &out);
	static void Clear(SerializeableQueue &in, SerializeableQueue &out);
	static void Close(SerializeableQueue &in, SerializeableQueue &out);
	static void SelectIndex(SerializeableQueue &in, SerializeableQueue &out);
	static void IsOpen(SerializeableQueue &in, SerializeableQueue &out);
	static void BlockGetCaption(SerializeableQueue &in, SerializeableQueue &out);
	static void BlockGetText(SerializeableQueue &in, SerializeableQueue &out);
	static void Block(SerializeableQueue &in, SerializeableQueue &out);
	static void BlockHasBlockedDialog(SerializeableQueue &in, SerializeableQueue &out);
	static void BlockHasNeedBlocking(SerializeableQueue &in, SerializeableQueue &out);
};
