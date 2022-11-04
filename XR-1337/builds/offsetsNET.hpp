#pragma once

constexpr DWORD dwName = 0x30C;
constexpr DWORD dwMoney = 0x2EC;
constexpr DWORD dwHP = 0x4;
constexpr DWORD dwStamina = 0x114;
constexpr DWORD dwWeight = 0x5C;
constexpr DWORD dwFov = 0x34;
constexpr DWORD dwCurrentWeapon = 0x14;
constexpr DWORD dwActorHudManagerBase = 0x4C;
constexpr DWORD dwCrosshairDelayInfo = 0x4;
constexpr DWORD dwTargetIsInCrosshair = 0x8;
constexpr DWORD dwTargetType = 0x14;
constexpr DWORD dwFireState = 0x98030;
constexpr DWORD dwActorInventory = 0x2E4;
constexpr DWORD dwCoordX = 0xBC;
constexpr DWORD dwCoordY = 0xC0;
constexpr DWORD dwCoordZ = 0xC4;
constexpr DWORD dwWeaponSelected = 0x14;

namespace initialized
{
	namespace actor
	{
		offset_module name = _Init_offset({ signatures::dwActor, offsets::dwName });

		offset_module stamina = _Init_offset({ signatures::dwActor,
			signatures::dwActorCondition, offsets::dwStamina });

		offset_module HP = _Init_offset({ signatures::dwActor,
			signatures::dwActorCondition, offsets::dwHP });

		offset_module money = _Init_offset({ signatures::dwActor, offsets::dwMoney });

		offset_module fov = _Init_offset({ signatures::dwActor, signatures::dwActorCamera, offsets::dwFov });
		offset_module weight = _Init_offset({ signatures::dwActor, offsets::dwActorInventory, offsets::dwWeight });

		offset_module coordX = _Init_offset({ signatures::dwActor, signatures::dwActorCamera, offsets::dwCoordX });
		offset_module coordY = _Init_offset({ signatures::dwActor, signatures::dwActorCamera, offsets::dwCoordY });
		offset_module coordZ = _Init_offset({ signatures::dwActor, signatures::dwActorCamera, offsets::dwCoordZ });

		offset_module targetType = _Init_offset({ signatures::dwHudManager, offsets::dwActorHudManagerBase,
			offsets::dwTargetIsInCrosshair, offsets::dwTargetType }, "xrEngine.exe");

		offset_module fireState = _Init_offset({ offsets::dwFireState }, "xrEngine.exe");

		offset_module crosshairDelayInfo = _Init_offset({ signatures::dwHudManager, offsets::dwActorHudManagerBase,
			offsets::dwCrosshairDelayInfo }, "xrEngine.exe");

		offset_module weaponIsInHands = _Init_offset({ signatures::dwActorWeapon, offsets::dwCurrentWeapon });
	}
}