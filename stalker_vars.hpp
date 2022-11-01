#pragma once

namespace stalkerNET
{
	namespace signatures
	{
		constexpr size_t StaminaRunDec = 0xF9461;
		constexpr size_t StaminaJumpDec = 0xF93AC;
		constexpr size_t MoneyChange = 0x33D9F6;
	}

	namespace fire_state
	{
		constexpr size_t can_shoot = 7933;
		constexpr size_t cant_shoot = 7421;
	}

	namespace target_type
	{
		constexpr size_t alive = 29;
		constexpr size_t non_alive = 13;
	};
}