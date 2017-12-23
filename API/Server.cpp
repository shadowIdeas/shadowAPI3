#include "stdafx.h"
#include "Server.h"
#include "SerializeableQueue.h"
#include "ServerAPIGeneral.h"
#include "ServerAPIPlayer.h"
#include "ServerAPIOverlayText.h"
#include "ServerAPISAMPChat.h"

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

	// Player
	AddFunction(PacketIdentifier::Player_GetHealth, ServerAPIPlayer::GetHealth);
	AddFunction(PacketIdentifier::Player_GetArmor, ServerAPIPlayer::GetArmor);
	AddFunction(PacketIdentifier::Player_GetYaw, ServerAPIPlayer::GetYaw);
	AddFunction(PacketIdentifier::Player_GetX, ServerAPIPlayer::GetX);
	AddFunction(PacketIdentifier::Player_GetY, ServerAPIPlayer::GetY);
	AddFunction(PacketIdentifier::Player_GetZ, ServerAPIPlayer::GetZ);
	AddFunction(PacketIdentifier::Player_GetPosition, ServerAPIPlayer::GetPosition);
	AddFunction(PacketIdentifier::Player_InInterior, ServerAPIPlayer::InInterior);
	AddFunction(PacketIdentifier::Player_InVehicle, ServerAPIPlayer::InVehicle);
	AddFunction(PacketIdentifier::Player_IsDriver, ServerAPIPlayer::IsDriver);

	// Overlay::Text
	AddFunction(PacketIdentifier::Overlay_Text_Create, ServerAPIOverlayText::Create);
	AddFunction(PacketIdentifier::Overlay_Text_Delete, ServerAPIOverlayText::Delete);
	AddFunction(PacketIdentifier::Overlay_Text_SetColor, ServerAPIOverlayText::SetColor);
	AddFunction(PacketIdentifier::Overlay_Text_SetX, ServerAPIOverlayText::SetX);
	AddFunction(PacketIdentifier::Overlay_Text_SetY, ServerAPIOverlayText::SetY);
	AddFunction(PacketIdentifier::Overlay_Text_SetText, ServerAPIOverlayText::SetText);
	AddFunction(PacketIdentifier::Overlay_Text_SetSize, ServerAPIOverlayText::SetSize);
	AddFunction(PacketIdentifier::Overlay_Text_GetTextExtent, ServerAPIOverlayText::GetExtent);

	// SAMP::Chat
	AddFunction(PacketIdentifier::SAMP_Chat_Send, ServerAPISAMPChat::Send);
	AddFunction(PacketIdentifier::SAMP_Chat_AddMessage1, ServerAPISAMPChat::AddMessage1);
	AddFunction(PacketIdentifier::SAMP_Chat_AddMessage2, ServerAPISAMPChat::AddMessage2);
	AddFunction(PacketIdentifier::SAMP_Chat_GetText, ServerAPISAMPChat::GetText);
	AddFunction(PacketIdentifier::SAMP_Chat_SetText, ServerAPISAMPChat::SetText);
	AddFunction(PacketIdentifier::SAMP_Chat_GetBufferMessage, ServerAPISAMPChat::GetBufferMessage);
	AddFunction(PacketIdentifier::SAMP_Chat_AddBufferMessage, ServerAPISAMPChat::AddBufferMessage);
	AddFunction(PacketIdentifier::SAMP_Chat_SetCursorPosition1, ServerAPISAMPChat::SetCursorPosition);
	AddFunction(PacketIdentifier::SAMP_Chat_SetCursorPosition2, ServerAPISAMPChat::SetCursorPosition2);
	AddFunction(PacketIdentifier::SAMP_Chat_Toggle, ServerAPISAMPChat::Toggle);
	AddFunction(PacketIdentifier::SAMP_Chat_Clear, ServerAPISAMPChat::Clear);
	AddFunction(PacketIdentifier::SAMP_Chat_IsOpen, ServerAPISAMPChat::IsOpen);
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