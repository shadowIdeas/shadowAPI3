#include "stdafx.h"
#include "ServerAPISAMPPlayer.h"
#include "NativeSAMPPlayer.h"

void ServerAPISAMPPlayer::GetLocalName(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPPlayer::GetLocalName());
}

void ServerAPISAMPPlayer::GetLocalId(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeSAMPPlayer::GetLocalId());
}

void ServerAPISAMPPlayer::GetNameById(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPPlayer::GetNameById(in.ReadInteger()));
}

void ServerAPISAMPPlayer::GetIdByName(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeSAMPPlayer::GetIdByName(in.ReadString()));
}

void ServerAPISAMPPlayer::GetFullName(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPPlayer::GetFullName(in.ReadString()));
}