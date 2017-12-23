#include "stdafx.h"
#include "Client.h"

Client::Client()
{
	while (!WaitNamedPipe(L"\\\\.\\pipe\\EBIP0", NMPWAIT_WAIT_FOREVER))
		Sleep(20);
	_writePipe = CreateFile(L"\\\\.\\pipe\\EBIP0", GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

	while (!WaitNamedPipe(L"\\\\.\\pipe\\EBIP1", NMPWAIT_WAIT_FOREVER))
		Sleep(20);
	_readPipe = CreateFile(L"\\\\.\\pipe\\EBIP1", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);

	int error = GetLastError();

	DWORD mode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(_readPipe, &mode, 0, 0);
	SetNamedPipeHandleState(_writePipe, &mode, 0, 0);

	for (size_t i = 0; i < ARRAYSIZE(_events); i++)
	{
		_events[i] = CreateEvent(0, 1, 0, 0);
		_used[i] = false;
		_out[i] = nullptr;
	}

	_running = true;
	_readThread = std::thread(&Client::ReadThread, this);
}

Client::~Client()
{
	CloseHandle(_readPipe);
	CloseHandle(_writePipe);

	_running = false;
	if (_readThread.joinable())
		_readThread.join();
}

std::shared_ptr<ClientMessage> Client::CreateMessage(PacketIdentifier identifier)
{
	auto message = std::make_shared<ClientMessage>(identifier);

	return message;
}

void Client::Write(std::shared_ptr<ClientMessage> message)
{
	int id = -1;
	for (size_t i = 0; i < ARRAYSIZE(_events); i++)
	{
		if (!_used[i])
		{
			_used[i] = true;
			id = i;
			break;
		}
	}

	if (id == -1)
	{
		// TODO
		DebugBreak();
	}

	SerializeableQueue queue;
	queue.WriteInteger(id);
	queue.WriteRawBytes(message->GetInput().GetData());

	auto data = queue.GetData();
	DWORD bytesWritten = 0;
	WriteFile(_writePipe, data.data(), data.size(), &bytesWritten, 0);

	WaitForSingleObject(_events[id], INFINITE);

	auto output = _out[id];
	message->SetResponse(_out[id]);

	_out[id] = nullptr;
	ResetEvent(_events[id]);
	_used[id] = false;
}

int Client::FastReadInteger(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);
	return message->GetResponse()->ReadInteger();
}

float Client::FastReadFloat(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);
	return message->GetResponse()->ReadFloat();
}

bool Client::FastReadBoolean(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);
	return message->GetResponse()->ReadBoolean();
}

std::wstring Client::FastReadString(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);
	return message->GetResponse()->ReadString();
}

void Client::FastWriteVoid(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);
}

void Client::FastWriteInteger(PacketIdentifier identifier, int i)
{
	auto message = CreateMessage(identifier);
	message->GetInput().WriteInteger(i);
	Write(message);
}

void Client::FastWriteBoolean(PacketIdentifier identifier, bool b)
{
	auto message = CreateMessage(identifier);
	message->GetInput().WriteBoolean(b);
	Write(message);
}

void Client::FastWriteString(PacketIdentifier identifier, const std::wstring & s)
{
	auto message = CreateMessage(identifier);
	message->GetInput().WriteString(s);
	Write(message);
}

void Client::ReadThread()
{
	while (_running)
	{
		BYTE buffer[512 * 128] = {};
		DWORD bytesRead = 0;

		bool success = ReadFile(_readPipe, buffer, 512 * 128, &bytesRead, 0);

		if (!success || bytesRead == 0)
		{
			// TODO
			DebugBreak();
		}

		std::vector<BYTE> bytes;
		for (size_t i = 0; i < bytesRead; i++)
			bytes.push_back(buffer[i]);

		auto in = std::make_shared<SerializeableQueue>(bytes);
		int id = in->ReadInteger();

		_out[id] = in;
		SetEvent(_events[id]);
	}
}