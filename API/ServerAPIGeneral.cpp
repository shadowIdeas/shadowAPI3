#include "stdafx.h"
#include "ServerAPIGeneral.h"
#include "NativeGeneral.h"

void ServerAPIGeneral::Useless(SerializeableQueue & in, SerializeableQueue & out)
{
	int i = in.ReadInteger();
	out.WriteInteger(i * 2);
}

void ServerAPIGeneral::Useless1(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(18);
}

void ServerAPIGeneral::GetWeatherId(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteInteger(NativeGeneral::GetWeatherId());
}
