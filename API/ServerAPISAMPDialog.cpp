#include "stdafx.h"
#include "ServerAPISAMPDialog.h"
#include "NativeSAMPDialog.h"

void ServerAPISAMPDialog::GetText(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPDialog::GetText());
}

void ServerAPISAMPDialog::SetText(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPDialog::SetText(in.ReadString());
}

void ServerAPISAMPDialog::SetCursorPosition1(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPDialog::SetCursorPosition(in.ReadInteger());
}

void ServerAPISAMPDialog::SetCursorPosition2(SerializeableQueue & in, SerializeableQueue & out)
{
	int indexStart = in.ReadInteger();
	int indexEnd = in.ReadInteger();
	NativeSAMPDialog::SetCursorPosition(indexStart, indexEnd);
}

void ServerAPISAMPDialog::GetId(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeSAMPDialog::GetId());
}

void ServerAPISAMPDialog::GetStringCount(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeSAMPDialog::GetStringCount());
}

void ServerAPISAMPDialog::GetStringByIndex(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPDialog::GetStringByIndex(in.ReadInteger()));
}

void ServerAPISAMPDialog::Clear(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPDialog::Clear();
}

void ServerAPISAMPDialog::Close(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPDialog::Close(in.ReadInteger());
}

void ServerAPISAMPDialog::SelectIndex(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPDialog::SelectIndex(in.ReadInteger());
}

void ServerAPISAMPDialog::IsOpen(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeSAMPDialog::IsOpen());
}

void ServerAPISAMPDialog::BlockGetCaption(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPDialog::BlockGetCaption());
}

void ServerAPISAMPDialog::BlockGetText(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPDialog::BlockGetText());
}

void ServerAPISAMPDialog::Block(SerializeableQueue & in, SerializeableQueue & out)
{
	int id = in.ReadInteger();
	std::wstring string = in.ReadString();
	NativeSAMPDialog::Block(id, string);
}

void ServerAPISAMPDialog::BlockHasBlockedDialog(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeSAMPDialog::BlockHasBlockedDialog());
}

void ServerAPISAMPDialog::BlockHasNeedBlocking(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativeSAMPDialog::BlockHasNeedBlocking());
}