#pragma once
#include "SerializeableQueue.h"

static class ServerAPISAMPPlayer
{
public:
	static void GetLocalName(SerializeableQueue &in, SerializeableQueue &out);
	static void GetLocalId(SerializeableQueue &in, SerializeableQueue &out);
	static void GetNameById(SerializeableQueue &in, SerializeableQueue &out);
	static void GetIdByName(SerializeableQueue &in, SerializeableQueue &out);
	static void GetFullName(SerializeableQueue &in, SerializeableQueue &out);
};
