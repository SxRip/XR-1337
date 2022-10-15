#pragma once
#include "offsets/offsets.hpp"
#include <Windows.h>

template <class _Ptr_value_type>
class _Offset_Ptr
{
public:

	_Offset_Ptr() : _ptr{}
	{}

	_Offset_Ptr(const _Offset_Ptr& ptr) : _ptr{ ptr._ptr }
	{}

	_Offset_Ptr(_Ptr_value_type* ptr)
		: _ptr{ ptr }
	{}

	inline _Ptr_value_type* get_ptr() const noexcept { return _ptr; }


	inline void operator=(_Ptr_value_type _val)
	{
		if (_ptr)
			*_ptr = _val;
	}

	inline bool operator==(_Ptr_value_type _val)
	{
		if (_ptr)
			return *_ptr == _val;
		return false;
	}

	inline bool operator==(const _Offset_Ptr& _offsetObj)
	{
		return _offsetObj._ptr == _ptr;
	}

	//checking if the pointer of bool type has true
	inline operator bool() const
	{
		if (_ptr)
			return *_ptr >= 1;
		return false;
	}

private:
	_Ptr_value_type* _ptr;
};

class Memory
{
public:
	using pair_offsets_vector_baseoffset = std::pair<std::vector<DWORD>, IOffsetBase*>;
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
				return reinterpret_cast<_Ptr_value_type*>(dwClientBase + _Offsets[i]);

			dwClientBase = *reinterpret_cast<DWORD*>(dwClientBase + _Offsets[i]);

			if (!dwClientBase)
				return nullptr;
		}
		return nullptr;
	}

	template <class _Ptr_value_type>
	_Offset_Ptr<_Ptr_value_type> get_pointer(const pair_offsets_vector_baseoffset& _Offsets)
	{
		return get_pointer<_Ptr_value_type>(_Offsets.first, _Offsets.second->get_module());
	}
};