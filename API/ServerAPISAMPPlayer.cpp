#include "stdafx.h"
#include "ServerAPISAMPPlayer.h"
#include "NativeSAMPPlayer.h"

SerializeFunction(ServerAPISAMPPlayer::GetLocalName)
{
	out.WriteString(NativeSAMPPlayer::GetLocalName());
}

SerializeFunction(ServerAPISAMPPlayer::GetLocalId)
{
	out.WriteInteger(NativeSAMPPlayer::GetLocalId());
}

SerializeFunction(ServerAPISAMPPlayer::GetNameById)
{
	out.WriteString(NativeSAMPPlayer::GetNameById(in.ReadInteger()));
}

SerializeFunction(ServerAPISAMPPlayer::GetIdByName)
{
	out.WriteInteger(NativeSAMPPlayer::GetIdByName(in.ReadString()));
}

SerializeFunction(ServerAPISAMPPlayer::GetFullName)
{
	out.WriteString(NativeSAMPPlayer::GetFullName(in.ReadString()));
}