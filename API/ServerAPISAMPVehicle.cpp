#include "stdafx.h"
#include "ServerAPISAMPVehicle.h"
#include "NativeSAMPVehicle.h"

SerializeFunction(ServerAPISAMPVehicle::GetNumberplate)
{
	out.WriteString(NativeSAMPVehicle::GetNumberplate());
}

SerializeFunction(ServerAPISAMPVehicle::ToggleSiren)
{
	NativeSAMPVehicle::ToggleSiren(in.ReadBoolean());
}