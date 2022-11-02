#pragma once

namespace actor
{
	offset_module name = make_pair({ signatures::dwActorMP, offsets::dwName });

	offset_module stamina = make_pair({ signatures::dwActorMP,
		signatures::dwActorCondition, offsets::dwStamina });

	offset_module HP = make_pair({ signatures::dwActorMP,
		signatures::dwActorCondition, offsets::dwHP });
	offset_module Fov = make_pair({signatures::dwActorMP, signatures::dwActorCamera, offsets::dwFov});
}