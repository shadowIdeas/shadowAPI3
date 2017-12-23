#include "stdafx.h"
#include "ServerAPISAMPChat.h"
#include "NativeSAMPChat.h"

void ServerAPISAMPChat::Send(SerializeableQueue & in, SerializeableQueue & out)
{
	std::wstring text = in.ReadString();

	NativeSAMPChat::Send(text);
}

void ServerAPISAMPChat::AddMessage1(SerializeableQueue & in, SerializeableQueue & out)
{
	std::wstring text = in.ReadString();

	NativeSAMPChat::AddMessage(text);
}

void ServerAPISAMPChat::AddMessage2(SerializeableQueue & in, SerializeableQueue & out)
{
	std::wstring text = in.ReadString();
	int color = in.ReadInteger();

	NativeSAMPChat::AddMessage(text, color);
}

void ServerAPISAMPChat::GetText(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPChat::GetText());
}

void ServerAPISAMPChat::SetText(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPChat::SetText(in.ReadString());
}

void ServerAPISAMPChat::GetBufferMessage(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPChat::GetBufferMessage(in.ReadInteger()));
}

void ServerAPISAMPChat::AddBufferMessage(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPChat::AddBufferMessage(in.ReadString());
}

void ServerAPISAMPChat::SetCursorPosition(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPChat::SetCursorPosition(in.ReadInteger());
}

void ServerAPISAMPChat::SetCursorPosition2(SerializeableQueue & in, SerializeableQueue & out)
{
	int indexStart = in.ReadInteger();
	int indexEnd = in.ReadInteger();
	NativeSAMPChat::SetCursorPosition(indexStart, indexEnd);
}

void ServerAPISAMPChat::Toggle(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPChat::Toggle(in.ReadBoolean());
}

void ServerAPISAMPChat::Clear(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPChat::Clear();
}

void ServerAPISAMPChat::IsOpen(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeSAMPChat::IsOpen());
}