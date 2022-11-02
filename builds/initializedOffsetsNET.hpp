#pragma once

namespace actor
{
	offset_module name = make_pair({ signatures::dwActor, offsets::dwName });

	offset_module stamina = make_pair({ signatures::dwActor,
		signatures::dwActorCondition, offsets::dwStamina });

	offset_module HP = make_pair({ signatures::dwActor,
		signatures::dwActorCondition, offsets::dwHP });

	offset_module fov = make_pair({ signatures::dwActor, signatures::dwActorCamera, offsets::dwFov });
	offset_module weight = make_pair({ signatures::dwActor, offsets::dwActorInventory, offsets::dwWeight });

	offset_module CoordX = make_pair({ signatures::dwHudManager, offsets::dwCoordX });
	offset_module CoordY = make_pair({ signatures::dwHudManager, offsets::dwCoordY });
	offset_module CoordZ = make_pair({ signatures::dwHudManager, offsets::dwCoordZ });
}