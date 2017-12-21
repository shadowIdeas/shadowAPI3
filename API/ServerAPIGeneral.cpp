#include "stdafx.h"
#include "ServerAPIGeneral.h"

void ServerAPIGeneral::Useless(SerializeableQueue & in, SerializeableQueue & out)
{
	int i = in.ReadInteger();
	out.WriteInteger(i * 2);
}