#include "stdafx.h"
#include "ServerAPISAMPDialog.h"
#include "NativeSAMPDialog.h"

SerializeFunction(ServerAPISAMPDialog::GetText)
{
	out.WriteString(NativeSAMPDialog::GetText());
}

SerializeFunction(ServerAPISAMPDialog::SetText)
{
	NativeSAMPDialog::SetText(in.ReadString());
}

SerializeFunction(ServerAPISAMPDialog::SetCursorPosition1)
{
	NativeSAMPDialog::SetCursorPosition(in.ReadInteger());
}

SerializeFunction(ServerAPISAMPDialog::SetCursorPosition2)
{
	int indexStart = in.ReadInteger();
	int indexEnd = in.ReadInteger();
	NativeSAMPDialog::SetCursorPosition(indexStart, indexEnd);
}

SerializeFunction(ServerAPISAMPDialog::GetId)
{
	out.WriteInteger(NativeSAMPDialog::GetId());
}

SerializeFunction(ServerAPISAMPDialog::GetStringCount)
{
	out.WriteInteger(NativeSAMPDialog::GetStringCount());
}

SerializeFunction(ServerAPISAMPDialog::GetStringByIndex)
{
	out.WriteString(NativeSAMPDialog::GetStringByIndex(in.ReadInteger()));
}

SerializeFunction(ServerAPISAMPDialog::Clear)
{
	NativeSAMPDialog::Clear();
}

SerializeFunction(ServerAPISAMPDialog::Close)
{
	NativeSAMPDialog::Close(in.ReadInteger());
}

SerializeFunction(ServerAPISAMPDialog::SelectIndex)
{
	NativeSAMPDialog::SelectIndex(in.ReadInteger());
}

SerializeFunction(ServerAPISAMPDialog::IsOpen)
{
	out.WriteBoolean(NativeSAMPDialog::IsOpen());
}

SerializeFunction(ServerAPISAMPDialog::BlockGetCaption)
{
	out.WriteString(NativeSAMPDialog::BlockGetCaption());
}

SerializeFunction(ServerAPISAMPDialog::BlockGetText)
{
	out.WriteString(NativeSAMPDialog::BlockGetText());
}

SerializeFunction(ServerAPISAMPDialog::Block)
{
	int id = in.ReadInteger();
	std::wstring string = in.ReadString();
	NativeSAMPDialog::Block(id, string);
}

SerializeFunction(ServerAPISAMPDialog::BlockHasBlockedDialog)
{
	out.WriteBoolean(NativeSAMPDialog::BlockHasBlockedDialog());
}

SerializeFunction(ServerAPISAMPDialog::BlockHasNeedBlocking)
{
	out.WriteBoolean(NativeSAMPDialog::BlockHasNeedBlocking());
}