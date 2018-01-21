#include "stdafx.h"
#include "SerializeableQueue.h"
#include <memory>

SerializeableQueue::SerializeableQueue()
{
	_dataIndex = 0;
}

SerializeableQueue::SerializeableQueue(std::vector<BYTE> data)
{
	_data = data;
	_dataIndex = 0;
}

SerializeableQueue::~SerializeableQueue()
{
}

void SerializeableQueue::WriteInteger(int i)
{
	PacketTypeData data;
	data.identifier = PacketTypeIdentifier::Integer;
	data.size = 4;

	data.data.push_back((BYTE)(i >> 24));
	data.data.push_back((BYTE)(i >> 16));
	data.data.push_back((BYTE)(i >> 8));
	data.data.push_back((BYTE)(i >> 0));

	EnqueueNext(data);
}

void SerializeableQueue::WriteFloat(float f)
{
	PacketTypeData data;
	data.identifier = PacketTypeIdentifier::Float;
	data.size = 4;

	unsigned char *bytes = reinterpret_cast<unsigned char*>(&f);

	data.data.push_back(bytes[0]);
	data.data.push_back(bytes[1]);
	data.data.push_back(bytes[2]);
	data.data.push_back(bytes[3]);

	EnqueueNext(data);
}

void SerializeableQueue::WriteBoolean(bool b)
{
	PacketTypeData data;
	data.identifier = PacketTypeIdentifier::Boolean;
	data.size = 1;

	data.data.push_back(b ? 1 : 0);

	EnqueueNext(data);
}

void SerializeableQueue::WriteString(const std::wstring & s)
{
	PacketTypeData data;
	data.identifier = PacketTypeIdentifier::String;
	data.size = sizeof(wchar_t)*s.length();

	for (size_t i = 0; i < s.length(); i++)
	{
		wchar_t c = s.at(i);
		data.data.push_back(((UCHAR*)&c)[0]);
		data.data.push_back(((UCHAR*)&c)[1]);
	}

	EnqueueNext(data);
}

void SerializeableQueue::WriteRawBytes(std::vector<BYTE>& bytes)
{
	for (size_t i = 0; i < bytes.size(); i++)
		_data.push_back(bytes[i]);
}

void SerializeableQueue::WriteRawByte(BYTE b)
{
	_data.push_back(b);
}

int SerializeableQueue::ReadInteger()
{
	PacketTypeData data = DequeueNext();
	if (data.identifier != PacketTypeIdentifier::Integer)
		return 0;

	BYTE bytes[4] = { };
	bytes[0] = data.data[3];
	bytes[1] = data.data[2];
	bytes[2] = data.data[1];
	bytes[3] = data.data[0];

	int i = 0;
	memcpy_s(&i, 4, bytes, 4);

	return i;
}

float SerializeableQueue::ReadFloat()
{
	PacketTypeData data = DequeueNext();
	if (data.identifier != PacketTypeIdentifier::Float)
		return 0.0f;

	BYTE bytes[4] = {};
	bytes[0] = data.data[0];
	bytes[1] = data.data[1];
	bytes[2] = data.data[2];
	bytes[3] = data.data[3];

	float f = 0;
	memcpy_s(&f, 4, bytes, 4);

	return f;
}

bool SerializeableQueue::ReadBoolean()
{
	PacketTypeData data = DequeueNext();
	if (data.identifier != PacketTypeIdentifier::Boolean)
		return false;

	return data.data[0] == 1 ? true : false;
}

std::wstring SerializeableQueue::ReadString()
{
	PacketTypeData data = DequeueNext();
	if (data.identifier != PacketTypeIdentifier::String)
		return false;

	int length = data.size / 2;
	std::unique_ptr<wchar_t[]> s = std::make_unique<wchar_t[]>(length + 1);
	s.get()[length] = L'\0';

	for (size_t i = 0; i < length; i++)
		s.get()[i] = (wchar_t)((((wchar_t)data.data[i * 2]) << 0) | (((wchar_t)data.data[(i * 2) + 1]) << 8));

	return std::wstring(s.get());
}

std::vector<BYTE> SerializeableQueue::GetData()
{
	return _data;
}

void SerializeableQueue::EnqueueNext(PacketTypeData data)
{
	std::vector<BYTE> dataBytes;
	dataBytes.push_back((BYTE)data.identifier);
	dataBytes.push_back((BYTE)(data.size >> 24));
	dataBytes.push_back((BYTE)(data.size >> 16));
	dataBytes.push_back((BYTE)(data.size >> 8));
	dataBytes.push_back((BYTE)(data.size >> 0));

	// Real data
	for (size_t i = 0; i < data.data.size(); i++)
		dataBytes.push_back(data.data.at(i));

	// Move to global
	for (size_t i = 0; i < dataBytes.size(); i++)
		_data.push_back(dataBytes.at(i));
}

PacketTypeData SerializeableQueue::DequeueNext()
{
	PacketTypeData data;

	UINT dataIndexAdd = 0;
	data.identifier = (PacketTypeIdentifier)_data.at(_dataIndex + 0);
	data.size = ((int)_data.at(_dataIndex + 1) << 24) | ((int)_data.at(_dataIndex + 2) << 16) | ((int)_data.at(_dataIndex + 3) << 8) | ((int)_data.at(_dataIndex + 4) << 0);
	dataIndexAdd += 5;
	for (size_t i = 0; i < data.size; i++)
	{
		data.data.push_back(_data.at(_dataIndex + dataIndexAdd));
		dataIndexAdd++;
	}

	_dataIndex += dataIndexAdd;

	return data;
}