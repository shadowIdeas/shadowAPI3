#include "stdafx.h"
#include "Client.h"

Client::Client()
{
	_readPipe = CreateFile(L"\\\\.\\pipe\\EBIP0", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	_writePipe = CreateFile(L"\\\\.\\pipe\\EBIP1", GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

	DWORD mode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(_readPipe, &mode, 0, 0);
	SetNamedPipeHandleState(_writePipe, &mode, 0, 0);

	_readThread = std::thread(&Client::ReadThread, this);
}

Client::~Client()
{
}

void Client::ReadThread()
{
}