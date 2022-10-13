#pragma once
#include "offsets/offsets.hpp"
#include <Windows.h>

class Memory
{
public:

	template <class _Ptr_value_type, class _Collection>
	_Ptr_value_type* get_pointer(const _Collection& _Offsets, const char* _Module = nullptr)
	{
		if (_Offsets.size() <= 0)
			return nullptr;

		DWORD dwClientBase =
			reinterpret_cast<DWORD>(GetModuleHandle(_Module ? _Module : "xrGame.dll"));
		_Ptr_value_type* pointer = nullptr;

		for (size_t i = 0; i < _Offsets.size(); ++i)
		{
			if (_Offsets[i] == 0)
				continue;

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

	template <class _Ptr_value_type, class _Collection, class _OffsetObject>
	_Ptr_value_type* get_pointer(const _Collection& _Offsets, const _OffsetObject& _Obj)
	{
		return get_pointer<_Ptr_value_type>(_Offsets, _Obj.get_module());
	}

	template <class _Ptr_value_type>
	_Ptr_value_type* get_pointer(const std::pair<std::vector<DWORD>, IOffsetBase*>& _Offsets)
	{
		return get_pointer<_Ptr_value_type>(_Offsets.first, _Offsets.second->get_module());
	}
};