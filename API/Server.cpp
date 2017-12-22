#include "stdafx.h"
#include "Server.h"
#include "SerializeableQueue.h"
#include "ServerAPIGeneral.h"

#define AddFunction(identifier, func) _functions.push_back(std::make_pair<PacketIdentifier, std::function<void(SerializeableQueue&, SerializeableQueue&)>>(identifier, &func))

Server::Server()
{
	RegisterFunctions();

	_readPipe = CreateNamedPipeW(L"\\\\.\\pipe\\EBIP0", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, 1, 512 * 128, 512 * 128, 5000, 0);
	_writePipe = CreateNamedPipeW(L"\\\\.\\pipe\\EBIP1", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE, 1, 512 * 128, 512 * 128, 5000, 0);

	_readThread = std::thread(&Server::ReadThread, this);
}

Server::~Server()
{
}

void Server::RegisterFunctions()
{
	AddFunction(PacketIdentifier::Useless, ServerAPIGeneral::Useless);
	AddFunction(PacketIdentifier::Useless1, ServerAPIGeneral::Useless1);
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
				DisconnectNamedPipe(_readPipe);
				DisconnectNamedPipe(_writePipe);

				WaitForClient();
				continue;
			}
		}

		std::vector<BYTE> bytes;
		for (size_t i = 0; i < bytesRead; i++)
			bytes.push_back(buffer[i]);

		auto in = SerializeableQueue(bytes);
		auto out = SerializeableQueue();

		int id = in.ReadInteger();
		PacketTypeIdentifier identifier = (PacketTypeIdentifier)in.ReadInteger();

		out.WriteInteger(id);

		// Call API function
		for (size_t i = 0; i < _functions.size(); i++)
		{
			auto pair = _functions[i];
			if (pair.first == identifier)
			{
				pair.second(in, out);
				break;
			}
		}

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
	{
		connected = ConnectNamedPipe(_readPipe, 0);
		if (!connected)
		{
			DWORD error = GetLastError();
			if (error == ERROR_PIPE_CONNECTED)
			{
				connected = true;
			}
		}
	}

	connected = false;
	while (!connected)
	{
		connected = ConnectNamedPipe(_writePipe, 0);

		if (!connected)
		{
			DWORD error = GetLastError();
			if (error == ERROR_PIPE_CONNECTED)
			{
				connected = true;
			}
		}
	}
}