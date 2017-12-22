#include "stdafx.h"
#include "ServerAPIGeneral.h"

void ServerAPIGeneral::Useless(SerializeableQueue & in, SerializeableQueue & out)
{
	int i = in.ReadInteger();
	out.WriteInteger(i * 2);
}

void ServerAPIGeneral::Useless1(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(18);
}