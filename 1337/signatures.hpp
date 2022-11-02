#pragma once

namespace signatures
{
#ifdef STALKERNET
	#include "builds/signaturesNET.hpp"
#endif // 

#ifdef OMP
#include "../builds/signaturesOMP.hpp"
#endif // OMP

#ifdef XRMPE
#include "../builds/signaturesXRMPE.hpp"
#endif // XRMPE
}