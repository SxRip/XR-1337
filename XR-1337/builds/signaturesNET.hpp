#pragma once

constexpr DWORD dwActor = 0x6ECC04;
constexpr DWORD dwActorCondition = 0x9D8;
constexpr DWORD dwActorCamera = 0x5A0;
constexpr DWORD dwActorWeapon = 0x6F0C74;
constexpr DWORD dwHudManager = 0x992D4;

namespace initialized
{
	signature staminaRunDec(0xF9461, 6);
	signature staminaJumpDec(0xF93AC, 6);
	signature moneyChange(0x33D9F6, 3);
	signature gameWeightCheck(0x33947A, 5);
}