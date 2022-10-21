#pragma once
#include "offsets/offsets.hpp"
#include <Windows.h>

template <class _Ptr_value_type>
class _Offset_Ptr
{
public:

	_Offset_Ptr() : _ptr{} {}

	_Offset_Ptr(const _Offset_Ptr&& ptr) : _ptr{ ptr._ptr } {}
	_Offset_Ptr(const _Offset_Ptr& ptr) : _ptr{ ptr._ptr } {}

	_Offset_Ptr(_Ptr_value_type* ptr) : _ptr{ ptr } {}

	inline _Offset_Ptr& operator=(_Ptr_value_type _Val)
	{
		if (_ptr)
			*_ptr = _Val;
		return *this;
	}

	//!use only with the same type of a pointer.
	inline _Offset_Ptr& operator=(const _Offset_Ptr& _Ptr)
	{
		_ptr = _Ptr._ptr;
		return *this;
	}

	inline bool operator==(_Ptr_value_type _Val)
	{
		if (_ptr)
			return *_ptr == _Val;
		return false;
	}

	inline bool operator==(const _Offset_Ptr& _OffsetObj)
	{
		return _OffsetObj._ptr == _ptr;
	}

	//checking if a pointer of bool type has true
	inline operator bool() const
	{
		if (_ptr)
			return *_ptr != 0;
		return false;
	}

	inline _Ptr_value_type& operator*() const { return *_ptr; }

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