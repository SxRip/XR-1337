#pragma once

namespace game
{
#ifdef STALKERNET
#include "builds/game_varsNET.hpp"
#endif // STALKERNET

#ifdef OMP
#include "builds/game_varsOMP.hpp"
#endif // OMP

#ifdef XRMPE
#include "builds/game_varsXRMPE.hpp"
#endif // XRMPE
}