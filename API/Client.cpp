#include "stdafx.h"
#include "Client.h"

Client::Client()
{
	while (!WaitNamedPipe(L"\\\\.\\pipe\\EBIP0", NMPWAIT_WAIT_FOREVER))
		Sleep(20);
	_pipe = CreateFile(L"\\\\.\\pipe\\EBIP0", GENERIC_WRITE | GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

	DWORD mode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(_pipe, &mode, 0, 0);

	_freed = false;

	for (size_t i = 0; i < ARRAYSIZE(_events); i++)
	{
		_events[i] = CreateEvent(0, 1, 0, 0);
		_communicationEvents[i+2] = CreateEvent(0, 1, 0, 0);
		_used[i] = false;
		_out[i] = nullptr;
	}

	_running = true;
	_readThread = std::thread(&Client::CommunicationThread, this);
}

Client::~Client()
{
	CloseHandle(_pipe);

	_running = false;
	if (_readThread.joinable())
		_readThread.join();

	Free();
}

std::shared_ptr<ClientMessage> Client::CreateMessage(PacketIdentifier identifier)
{
	auto message = std::make_shared<ClientMessage>(identifier);
	return message;
}

void Client::Write(std::shared_ptr<ClientMessage> message)
{
	if (_freed)
	{
		message->Invalidate();
		return;
	}

	int id = -1;
	{
		std::lock_guard<std::mutex> guard(_idMutex);
		for (size_t i = 0; i < ARRAYSIZE(_events); i++)
		{
			if (!_used[i])
			{
				_used[i] = true;
				id = i;
				break;
			}
		}
	}

	// Wait until a ID is free
	while (id == -1)
	{
		Sleep(20);

		if (_freed)
		{
			message->Invalidate();
			return;
		}

		std::lock_guard<std::mutex> guard(_idMutex);
		for (size_t i = 0; i < ARRAYSIZE(_events); i++)
		{
			if (!_used[i])
			{
				_used[i] = true;
				id = i;
				break;
			}
		}
	}

	SerializeableQueue queue;
	queue.WriteInteger(id);
	queue.WriteRawBytes(message->GetInput().GetData());
	
	auto data = queue.GetData();
	_communicationData[id] = data;
	SetEvent(_communicationEvents[id+2]);
	WaitForSingleObject(_events[id], INFINITE);

	if (_freed)
	{
		message->Invalidate();
		return;
	}

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

	if (message->IsInvalid())
		return -1;
	
	return message->GetResponse()->ReadInteger();
}

float Client::FastReadFloat(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);

	if (message->IsInvalid())
		return 0.0f;

	return message->GetResponse()->ReadFloat();
}

bool Client::FastReadBoolean(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);

	if (message->IsInvalid())
		return false;

	return message->GetResponse()->ReadBoolean();
}

std::wstring Client::FastReadString(PacketIdentifier identifier)
{
	auto message = CreateMessage(identifier);
	Write(message);

	if (message->IsInvalid())
		return std::wstring();

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

void Client::CommunicationThread()
{
	
	HANDLE readEvent = CreateEvent(0, 1, 0, 0);
	HANDLE writeEvent = CreateEvent(0, 1, 0, 0);

	OVERLAPPED overlappedRead = { 0 };
	OVERLAPPED overlappedWrite = { 0 };
	overlappedRead.hEvent = readEvent;
	overlappedWrite.hEvent = writeEvent;

	_communicationEvents[0] = readEvent;
	_communicationEvents[1] = writeEvent;

	BYTE buffer[512 * 128] = {};
	DWORD bytesRead = 0;
	ReadFile(_pipe, buffer, 512 * 128, 0, &overlappedRead);

	while (_running)
	{
		DWORD triggeredEvent = WaitForMultipleObjects(64, _communicationEvents, false, INFINITE);
		switch (triggeredEvent)
		{
			case WAIT_OBJECT_0:
			{
				GetOverlappedResult(_pipe, &overlappedRead, &bytesRead, true);
				ResetEvent(readEvent);
				if (bytesRead == 0)
				{
					if (GetLastError() == ERROR_MORE_DATA)
						continue;

					Free();
					return;
				}

				std::vector<BYTE> bytes;
				for (size_t i = 0; i < bytesRead; i++)
					bytes.push_back(buffer[i]);

				auto in = std::make_shared<SerializeableQueue>(bytes);
				int id = in->ReadInteger();

				_out[id] = in;
				SetEvent(_events[id]);

				ResetEvent(readEvent);
				ReadFile(_pipe, buffer, 512 * 128, 0, &overlappedRead);
			}
			break;
			case WAIT_OBJECT_0+1:
			{
				ResetEvent(writeEvent);

				for (size_t i = 0; i < 62; i++)
				{
					DWORD eventIndex = i+2;
					bool triggered = WaitForSingleObjectEx(_communicationEvents[eventIndex], 0, true) != WAIT_TIMEOUT;
					if (triggered)
					{
						auto data = _communicationData[i];
						WriteFile(_pipe, data.data(), data.size(), 0, &overlappedWrite);
						ResetEvent(_communicationEvents[eventIndex]);
						break;
					}
				}
			}
			case WAIT_TIMEOUT:
			{

			}
			break;
			case WAIT_FAILED:
			{
				auto error = GetLastError();
			}
			break;
			default:
			{
				bool triggered = WaitForSingleObjectEx(writeEvent, 0, true) != WAIT_TIMEOUT;
				if (!triggered)
				{
					DWORD eventIndex = triggeredEvent;
					auto data = _communicationData[eventIndex - 2];
					WriteFile(_pipe, data.data(), data.size(), 0, &overlappedWrite);

					ResetEvent(_communicationEvents[eventIndex]);
				}
				
			}
			break;
		}
	}

	CloseHandle(readEvent);
	CloseHandle(writeEvent);
}

void Client::Free()
{
	if (!_freed)
	{
		_freed = true;

		for (size_t i = 0; i < ARRAYSIZE(_events); i++)
		{
			SetEvent(_events[i]);
			CloseHandle(_events[i]);
			CloseHandle(_communicationEvents[i + 2]);
		}

	}
}