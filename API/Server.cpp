#include "stdafx.h"
#include "Server.h"
#include "SerializeableQueue.h"

Server::Server()
{
	_readPipe = CreateNamedPipeW(L"\\\\.\\pipe\\EBIP0", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, 1, 512 * 128, 512 * 128, 5000, 0);
	_writePipe = CreateNamedPipeW(L"\\\\.\\pipe\\EBIP0", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE, 1, 512 * 128, 512 * 128, 5000, 0);

	_readThread = std::thread(&Server::ReadThread, this);
}

Server::~Server()
{
}

void Server::ReadThread()
{
	WaitForClient();
	// Just run for... ever!
	while (true)
	{
		BYTE buffer[512 * 128] = {};
		DWORD bytesRead = 0;

		bool success = ReadFile(_readPipe, buffer, 512 * 128, &bytesRead, 0);

		if (!success || bytesRead == 0)
		{
			if (GetLastError() == ERROR_BROKEN_PIPE)
			{
				WaitForClient();
				continue;
			}
		}

		std::vector<BYTE> bytes;
		for (size_t i = 0; i < bytesRead; i++)
			bytes.push_back(buffer[i]);

		auto in = SerializeableQueue(bytes);
		auto out = SerializeableQueue();

		// Call API function

		// Return
		auto data = out.GetData();
		DWORD bytesWritten = 0;
		WriteFile(_writePipe, data.data(), data.size(), &bytesWritten, 0);
	}
}

void Server::WaitForClient()
{
	bool connected = false;

	while (!connected)
		connected = ConnectNamedPipe(_readPipe, 0);

	while (!connected)
		connected = ConnectNamedPipe(_writePipe, 0);
}