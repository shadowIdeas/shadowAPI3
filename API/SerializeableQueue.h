#pragma once
#include "PacketTypeData.h"

#define SerializeFunction(name) void name(int clientId, SerializeableQueue &in, SerializeableQueue &out)
#define SerializeFunctionH(name) static void name(int clientId, SerializeableQueue &in, SerializeableQueue &out)

class SerializeableQueue
{
public:
	SerializeableQueue();
	SerializeableQueue(std::vector<BYTE> data);
	~SerializeableQueue();

	void WriteInteger(int i);
	void WriteFloat(float f);
	void WriteBoolean(bool b);
	void WriteString(const std::wstring &s);
	void WriteRawBytes(std::vector<BYTE> &bytes);
	void WriteRawByte(BYTE b);

	int ReadInteger();
	float ReadFloat();
	bool ReadBoolean();
	std::wstring ReadString();

	std::vector<BYTE> GetData();
private:
	std::vector<BYTE> _data;
	UINT _dataIndex;

	void EnqueueNext(PacketTypeData data);
	PacketTypeData DequeueNext();
};
