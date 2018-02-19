#include "stdafx.h"
#include "ServerAPIPlayer.h"
#include "NativePlayer.h"

SerializeFunction(ServerAPIPlayer::GetHealth)
{
	out.WriteInteger((int)NativePlayer::GetHealth());
}

SerializeFunction(ServerAPIPlayer::GetArmor)
{
	out.WriteInteger((int)NativePlayer::GetArmor());
}

SerializeFunction(ServerAPIPlayer::GetInteriorId)
{
	out.WriteInteger(NativePlayer::GetInteriorId());
}

SerializeFunction(ServerAPIPlayer::GetYaw)
{
	out.WriteFloat(NativePlayer::GetYaw());
}

SerializeFunction(ServerAPIPlayer::GetX)
{
	out.WriteFloat(NativePlayer::GetX());
}

SerializeFunction(ServerAPIPlayer::GetY)
{
	out.WriteFloat(NativePlayer::GetY());
}

SerializeFunction(ServerAPIPlayer::GetZ)
{
	out.WriteFloat(NativePlayer::GetZ());
}

SerializeFunction(ServerAPIPlayer::GetPosition)
{
	out.WriteFloat(NativePlayer::GetX());
	out.WriteFloat(NativePlayer::GetY());
	out.WriteFloat(NativePlayer::GetZ());
}

SerializeFunction(ServerAPIPlayer::InInterior)
{
	out.WriteBoolean(NativePlayer::InInterior());
}

SerializeFunction(ServerAPIPlayer::InVehicle)
{
	out.WriteBoolean(NativePlayer::InVehicle());
}

SerializeFunction(ServerAPIPlayer::IsDriver)
{
	out.WriteBoolean(NativePlayer::IsDriver());
}