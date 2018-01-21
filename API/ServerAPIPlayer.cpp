#include "stdafx.h"
#include "ServerAPIPlayer.h"
#include "NativePlayer.h"

void ServerAPIPlayer::GetHealth(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger((int)NativePlayer::GetHealth());
}

void ServerAPIPlayer::GetArmor(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger((int)NativePlayer::GetArmor());
}

void ServerAPIPlayer::GetInteriorId(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativePlayer::GetInteriorId());
}

void ServerAPIPlayer::GetYaw(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativePlayer::GetYaw());
}

void ServerAPIPlayer::GetX(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativePlayer::GetX());
}

void ServerAPIPlayer::GetY(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativePlayer::GetY());
}

void ServerAPIPlayer::GetZ(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativePlayer::GetZ());
}

void ServerAPIPlayer::GetPosition(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteFloat(NativePlayer::GetX());
	out.WriteFloat(NativePlayer::GetY());
	out.WriteFloat(NativePlayer::GetZ());
}

void ServerAPIPlayer::InInterior(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativePlayer::InInterior());
}

void ServerAPIPlayer::InVehicle(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativePlayer::InVehicle());
}

void ServerAPIPlayer::IsDriver(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteBoolean(NativePlayer::IsDriver());
}