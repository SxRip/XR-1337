#pragma once

namespace stalker
{
	namespace signatures
	{
		constexpr size_t StaminaRun = 0xF9461;
		constexpr size_t StaminaJump = 0xF93AC;
		constexpr size_t Money = 0x33D9F6;
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