#include "stdafx.h"
#include "ServerAPISAMPVehicle.h"
#include "NativeSAMPVehicle.h"

void ServerAPISAMPVehicle::GetNumberplate(SerializeableQueue & in, SerializeableQueue & out)
{
	out.WriteString(NativeSAMPVehicle::GetNumberplate());
}

void ServerAPISAMPVehicle::ToggleSiren(SerializeableQueue & in, SerializeableQueue & out)
{
	NativeSAMPVehicle::ToggleSiren(in.ReadBoolean());
}