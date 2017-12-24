#pragma once

enum PacketIdentifier
{
	Useless,
	Useless1,

	// Player
	Player_GetHealth,
	Player_GetArmor,
	Player_GetX,
	Player_GetY,
	Player_GetZ,
	Player_GetPosition,
	Player_GetYaw,
	Player_InInterior,
	Player_InVehicle,
	Player_IsDriver,

	// Vehicle
	Vehicle_GetSpeed,
	Vehicle_GetHealth,
	Vehicle_GetModelId,
	Vehicle_IsLightActive,
	Vehicle_IsLocked,
	Vehicle_IsEngineRunning,
	Vehicle_UseHorn,
	Vehicle_UseSiren,

	// Overlay Text
	Overlay_Text_Create,
	Overlay_Text_Delete,
	Overlay_Text_SetColor,
	Overlay_Text_SetX,
	Overlay_Text_SetY,
	Overlay_Text_SetMaxWidth,
	Overlay_Text_SetMaxHeight,
	Overlay_Text_SetActive,
	Overlay_Text_SetText,
	Overlay_Text_SetSize,
	Overlay_Text_SetUseMaxWidth,
	Overlay_Text_SetUseMaxHeight,
	Overlay_Text_GetTextExtent,

	// Overlay Box
	Overlay_Box_Create,
	Overlay_Box_Delete,
	Overlay_Box_SetColor,
	Overlay_Box_SetX,
	Overlay_Box_SetY,
	Overlay_Box_SetWidth,
	Overlay_Box_SetHeight,
	Overlay_Box_SetActive,

	// SAMP Player
	SAMP_Player_GetLocalName,
	SAMP_Player_GetLocalId,
	SAMP_Player_GetNameById,
	SAMP_Player_GetIdByName,
	SAMP_Player_GetFullName,

	// SAMP Vehicle
	SAMP_Vehicle_GetNumberplate,
	SAMP_Vehicle_ToggleSiren,

	// SAMP Chat
	SAMP_Chat_Send,
	SAMP_Chat_AddMessage1,
	SAMP_Chat_AddMessage2,
	SAMP_Chat_GetText,
	SAMP_Chat_SetText,
	SAMP_Chat_GetBufferMessage,
	SAMP_Chat_AddBufferMessage,
	SAMP_Chat_SetCursorPosition1,
	SAMP_Chat_SetCursorPosition2,
	SAMP_Chat_Toggle,
	SAMP_Chat_Clear,
	SAMP_Chat_IsOpen,

	// SAMP Dialog
	SAMP_Dialog_GetText,
	SAMP_Dialog_SetText,
	SAMP_Dialog_SetCursorPosition1,
	SAMP_Dialog_SetCursorPosition2,
	SAMP_Dialog_GetId,
	SAMP_Dialog_GetStringCount,
	SAMP_Dialog_GetStringByIndex,
	SAMP_Dialog_Clear,
	SAMP_Dialog_Close,
	SAMP_Dialog_SelectIndex,
	SAMP_Dialog_IsOpen,
	SAMP_Dialog_BlockGetCaption,
	SAMP_Dialog_BlockGetText,
	SAMP_Dialog_Block,
	SAMP_Dialog_BlockHasBlockedDialog,
	SAMP_Dialog_BlockHasNeedBlocking
};
