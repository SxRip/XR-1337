#pragma once
#include "offsets/offsets.h"

class Memory
{
public:

	template <class _Ptr_value_type, class _Collection>
	_Ptr_value_type* get_pointer(const _Collection& _Offsets)
	{
		DWORD dwClientBase = reinterpret_cast<DWORD>(GetModuleHandle("xrGame.dll"));
		_Ptr_value_type* pointer = nullptr;

		for (size_t i = 0; i < _Offsets.size(); ++i)
		{
			if (i == _Offsets.size() - 1)
			{
				pointer = reinterpret_cast<_Ptr_value_type*>(dwClientBase + _Offsets[i]);
				return pointer ? pointer : nullptr;
			}
			dwClientBase = *reinterpret_cast<DWORD*>(dwClientBase + _Offsets[i]);

			if (!dwClientBase)
				return nullptr;
		}
		return nullptr;
	}

	template <class _Ptr_value_type, class _Collection>
	_Ptr_value_type* get_pointer(const _Collection& _Offsets, const char* _Module)
	{
		DWORD dwClientBase = reinterpret_cast<DWORD>(GetModuleHandle(_Module));
		_Ptr_value_type* pointer = nullptr;

		for (size_t i = 0; i < _Offsets.size(); ++i)
		{
			if (i == _Offsets.size() - 1)
			{
				pointer = reinterpret_cast<_Ptr_value_type*>(dwClientBase + _Offsets[i]);
				return pointer ? pointer : nullptr;
			}
			dwClientBase = *reinterpret_cast<DWORD*>(dwClientBase + _Offsets[i]);

			if (!dwClientBase)
				return nullptr;
		}
		return nullptr;
	}

};

