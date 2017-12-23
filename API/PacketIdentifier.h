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

	// Overlay Text
	Overlay_Text_Create,
	Overlay_Text_Delete,
	Overlay_Text_SetColor,
	Overlay_Text_SetX,
	Overlay_Text_SetY,
	Overlay_Text_SetWidth,
	Overlay_Text_SetHeight,
	Overlay_Text_SetMaxWidth,
	Overlay_Text_SetMaxHeight,
	Overlay_Text_SetActive,
	Overlay_Text_SetText,
	Overlay_Text_SetSize,
	Overlay_Text_SetUseMaxWidth,
	Overlay_Text_SetUseMaxHeight,
	Overlay_Text_GetTextExtent,

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
};
