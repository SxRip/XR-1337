#pragma once
#include "offsets/offsets.hpp"
#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>

#pragma comment (lib, "ntdll.lib")

PPEB GetCurrentPebProcess()
{
	PROCESS_BASIC_INFORMATION ProcessInformation{};
	DWORD ReturnValue;

	NTSTATUS Ok = NtQueryInformationProcess(GetCurrentProcess(),
		ProcessBasicInformation, &ProcessInformation, sizeof(PROCESS_BASIC_INFORMATION), &ReturnValue);

	if (Ok != STATUS_SUCCESS || !ProcessInformation.PebBaseAddress)
		return nullptr;

	return ProcessInformation.PebBaseAddress;
}


bool BypassDebugging()
{
	PPEB ProcessPEB = GetCurrentPebProcess();

	if (!ProcessPEB)
		return false;

	if (static_cast<size_t>(ProcessPEB->BeingDebugged))
		ProcessPEB->BeingDebugged = 0;
	return true;
}

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

	inline _Offset_Ptr& operator+=(_Ptr_value_type _Val)
	{
		if (_ptr)
			*_ptr += _Val;
		return *this;
	}

	inline _Offset_Ptr& operator-=(_Ptr_value_type _Val)
	{
		if (_ptr)
			*_ptr -= _Val;
		return *this;
	}

	inline bool operator==(_Ptr_value_type _Val) const
	{
		if (_ptr)
			return *_ptr == _Val;
		return false;
	}

	inline bool operator==(const _Offset_Ptr& _Ptr) const noexcept
	{
		return _Ptr._ptr == _ptr;
	}

	//checking if a value of a bool pointer type has true
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

constexpr size_t NOP = 0x90;
class Memory
{
public:

	inline DWORD get_modulebase(const char* _Module) const noexcept
	{
		return reinterpret_cast<DWORD>(GetModuleHandle(_Module));
	}

	using pair_offsets_vector_baseoffset = std::pair<std::vector<DWORD>, IOffsetBase*>;
	template <class _Ptr_value_type, class _Ty>
	_Ptr_value_type* get_pointer(const std::vector<_Ty>& _Offsets, const char* _Module = nullptr)
	{
		if (_Offsets.size() <= 0)
			return nullptr;

		DWORD dwClientBase = get_modulebase(_Module ? _Module : "xrGame.dll");

		if (!dwClientBase)
			return nullptr;

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
	inline _Offset_Ptr<_Ptr_value_type> get_pointer(const pair_offsets_vector_baseoffset& _Pair)
	{
		return get_pointer<_Ptr_value_type>(_Pair.first, _Pair.second->get_module());
	}

	template <class _Ptr_value_type>
	inline _Offset_Ptr<_Ptr_value_type> get_pointer(DWORD _Offset, const char* _Module = nullptr) const noexcept
	{
		DWORD dwClientBase = get_modulebase(_Module ? _Module : "xrGame.dll");

		if (!dwClientBase)
			return nullptr;

		return reinterpret_cast<_Ptr_value_type*>(dwClientBase + _Offset);
	}

	inline bool path(DWORD& _Address, const char* _PathSign, size_t _Size) const noexcept
	{
		DWORD _protect;
		if (!VirtualProtect(&_Address, _Size, PAGE_READWRITE, &_protect))
			return false;

		memcpy(&_Address, _PathSign, _Size);

		if (!VirtualProtect(&_Address, _Size, _protect, &_protect))
			return false;
		return true;
	}

	inline bool path(DWORD&& _Address, const char* _PathSign, size_t _Size) const noexcept
	{
		return path(_Address, _PathSign, _Size);
	}

	inline bool path(_Offset_Ptr<DWORD>& _Ptr, const char* _PathSign, size_t _Size) const noexcept
	{
		return path(*_Ptr, _PathSign, _Size);
	}

	inline bool nop(DWORD& _Address, size_t _Size) const noexcept
	{
		DWORD _protect;
		if (!VirtualProtect(&_Address, _Size, PAGE_READWRITE, &_protect))
			return false;

		memset(&_Address, NOP, _Size);

		if (!VirtualProtect(&_Address, _Size, _protect, &_protect))
			return false;
		return true;
	}

	inline bool nop(DWORD&& _Address, size_t _Size) const noexcept
	{
		return nop(_Address, _Size);
	}

	inline bool nop(_Offset_Ptr<DWORD>& _Ptr, size_t _Size) const noexcept
	{
		return nop(*_Ptr, _Size);
	}

	//non secure version of the functions.
	inline void _path(DWORD& _Address, const char* _PathSign, size_t _Size) const noexcept
	{
		DWORD _protect;
		VirtualProtect(&_Address, _Size, PAGE_READWRITE, &_protect);

		memcpy(&_Address, _PathSign, _Size);

		VirtualProtect(&_Address, _Size, _protect, &_protect);
	}

	inline void _path(DWORD&& _Address, const char* _PathSign, size_t _Size) const noexcept
	{
		_path(_Address, _PathSign, _Size);
	}

	inline void _path(_Offset_Ptr<DWORD>& _Ptr, const char* _PathSign, size_t _Size) const noexcept
	{
		_path(*_Ptr, _PathSign, _Size);
	}

	inline void _nop(DWORD& _Address, size_t _Size) const noexcept
	{
		DWORD _protect;
		VirtualProtect(&_Address, _Size, PAGE_READWRITE, &_protect);

		memset(&_Address, 0x90, _Size);

		VirtualProtect(&_Address, _Size, _protect, &_protect);
	}

	inline void _nop(DWORD&& _Address, size_t _Size) const noexcept
	{
		_nop(_Address, _Size);
	}

	inline void _nop(_Offset_Ptr<DWORD> _Ptr, size_t _Size) const noexcept
	{
		_nop(*_Ptr, _Size);
	}
};