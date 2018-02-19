#include "stdafx.h"
#include "ServerAPISAMPChat.h"
#include "NativeSAMPChat.h"

SerializeFunction(ServerAPISAMPChat::Send)
{
	std::wstring text = in.ReadString();
	
	NativeSAMPChat::Send(text);
}

SerializeFunction(ServerAPISAMPChat::AddMessage1)
{
	std::wstring text = in.ReadString();

	NativeSAMPChat::AddMessage(text);
}

SerializeFunction(ServerAPISAMPChat::AddMessage2)
{
	std::wstring text = in.ReadString();
	int color = in.ReadInteger();

	NativeSAMPChat::AddMessage(text, color);
}

SerializeFunction(ServerAPISAMPChat::GetText)
{
	out.WriteString(NativeSAMPChat::GetText());
}

SerializeFunction(ServerAPISAMPChat::SetText)
{
	NativeSAMPChat::SetText(in.ReadString());
}

SerializeFunction(ServerAPISAMPChat::GetBufferMessage)
{
	out.WriteString(NativeSAMPChat::GetBufferMessage(in.ReadInteger()));
}

SerializeFunction(ServerAPISAMPChat::AddBufferMessage)
{
	NativeSAMPChat::AddBufferMessage(in.ReadString());
}

SerializeFunction(ServerAPISAMPChat::SetCursorPosition)
{
	NativeSAMPChat::SetCursorPosition(in.ReadInteger());
}

SerializeFunction(ServerAPISAMPChat::SetCursorPosition2)
{
	int indexStart = in.ReadInteger();
	int indexEnd = in.ReadInteger();
	NativeSAMPChat::SetCursorPosition(indexStart, indexEnd);
}

SerializeFunction(ServerAPISAMPChat::Toggle)
{
	NativeSAMPChat::Toggle(in.ReadBoolean());
}

SerializeFunction(ServerAPISAMPChat::Clear)
{
	NativeSAMPChat::Clear();
}

SerializeFunction(ServerAPISAMPChat::IsOpen)
{
	out.WriteBoolean(NativeSAMPChat::IsOpen());
}