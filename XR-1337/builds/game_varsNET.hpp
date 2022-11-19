#pragma once

namespace fire_state
{
	constexpr size_t can_shoot = 7933;
	constexpr size_t cant_shoot = 7421;
}

namespace player_state
{
	constexpr size_t stay = 65536;
	constexpr size_t moving = 0;
	constexpr size_t flying = 65792;
	constexpr size_t flyingWithStaminaWaste = 256;
	constexpr size_t readyToJump = 100;
}

namespace target_type
{
	constexpr size_t alive = 29;
	constexpr size_t non_alive = 13;
};