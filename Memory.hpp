#pragma once
#include "offsets/offsets.h"

class Memory
{
public:

	template <class _Ptr, class _Collection>
	_Ptr* get_pointer(const _Collection& _Offsets)
	{
		DWORD dwClientBase = reinterpret_cast<DWORD>(GetModuleHandle("xrGame.dll"));
		_Ptr* pointer = nullptr;

		for (size_t i = 0; i < _Offsets.size(); ++i)
		{
			if (i == _Offsets.size() - 1)
			{
				pointer = reinterpret_cast<_Ptr*>(dwClientBase + _Offsets[i]);
				break;
			}
			dwClientBase = *reinterpret_cast<DWORD*>(dwClientBase + _Offsets[i]);

			if (!dwClientBase)
				return nullptr;
		}

		return pointer ? pointer : nullptr;
	}
};

