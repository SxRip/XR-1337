#pragma once
#include <vector>
#include <Windows.h>
#include <winternl.h>
#include <map>
#include <string>

#pragma comment (lib, "ntdll.lib")

PPEB GetCurrentPebProcess();
bool BypassDebugging();

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

class signature;
constexpr size_t NOP = 0x90;

class Memory
{
private:
	std::map<std::string, DWORD> _alreadyLoadedModules;

	using const_map_interator = std::map<std::string, DWORD>::const_iterator;
	inline const_map_interator _Check_if_module_exist(const char* _Module) const noexcept
	{
		return std::find_if(_alreadyLoadedModules.cbegin(), _alreadyLoadedModules.cend(),
			[&](const std::pair<std::string, DWORD>& pair)
			{
				return pair.first == _Module;
			});
	}

	inline void _Init_base_iterator(const_map_interator& _Iterator, const char* _Module) noexcept
	{
		_Iterator = _Check_if_module_exist(_Module);
		if (_Iterator == _alreadyLoadedModules.cend())
		{
			_alreadyLoadedModules.emplace(_Module, get_modulebase(_Module));
			_Iterator = _Check_if_module_exist(_Module);
		}
	}

public:
	Memory() = default;

	using pair_offsets_module_vector = std::pair<std::vector<DWORD>, const char*>;

	inline DWORD get_modulebase(const char* _Module) const noexcept
	{
		return reinterpret_cast<DWORD>(GetModuleHandle(_Module));
	}

	template <class _Ptr_value_type, class _Ty>
	_Ptr_value_type* get_pointer(const std::vector<_Ty>& _Offsets, const char* _Module)
	{
		if (_Offsets.size() <= 0)
			return nullptr;

		const_map_interator BaseIterator;
		_Init_base_iterator(BaseIterator, _Module);

		DWORD dwClientBase = BaseIterator->second;

		if (!dwClientBase)
			return nullptr;

		for (size_t i = 0; i < _Offsets.size(); ++i)
		{
			if (i == _Offsets.size() - 1)
				return reinterpret_cast<_Ptr_value_type*>(dwClientBase + _Offsets[i]);

			dwClientBase = *reinterpret_cast<DWORD*>(dwClientBase + _Offsets[i]);

			if (!dwClientBase)
				return nullptr;
		}
		return nullptr;
	}

	template <class _Ptr_value_type>
	inline _Offset_Ptr<_Ptr_value_type> get_pointer(const pair_offsets_module_vector& _Pair)
	{
		return get_pointer<_Ptr_value_type>(_Pair.first, _Pair.second);
	}

	template <class _Ptr_value_type>
	inline _Offset_Ptr<_Ptr_value_type> get_pointer(DWORD _Offset, const char* _Module = "xrGame.dll") noexcept
	{
		const_map_interator BaseIterator;
		_Init_base_iterator(BaseIterator, _Module);
		DWORD dwClientBase = BaseIterator->second;

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

	bool path(signature& _Sign, const char* _PathSign, size_t _Size) const noexcept;

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

	inline bool nop(DWORD&& _Address, size_t _Size) const noexcept { return nop(_Address, _Size); }

	inline bool nop(_Offset_Ptr<DWORD>& _Ptr, size_t _Size) const noexcept { return nop(*_Ptr, _Size); }

	bool nop(signature& _Sign) const noexcept;

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

	void _path(signature& _Sign, const char* _PathSign, size_t _Size) const noexcept;

	inline void _nop(DWORD& _Address, size_t _Size) const noexcept
	{
		DWORD _protect;
		VirtualProtect(&_Address, _Size, PAGE_READWRITE, &_protect);

		memset(&_Address, NOP, _Size);

		VirtualProtect(&_Address, _Size, _protect, &_protect);
	}

	inline void _nop(DWORD&& _Address, size_t _Size) const noexcept { _nop(_Address, _Size); }

	inline void _nop(_Offset_Ptr<DWORD>& _Ptr, size_t _Size) const noexcept { _nop(*_Ptr, _Size); }

	void _nop(signature& _Sign) const noexcept;
};

class signature
{
public:
	signature(DWORD _Offset, size_t _BytesNopCount, const char* _Module = "xrGame.dll")
		: _nop_bytes{ _BytesNopCount }
	{
		if (!_mem)
			_mem = new Memory();
		_ptr = (*_mem).get_pointer<DWORD>(_Offset, _Module);
	}

	~signature()
	{
		if (_mem)
		{
			delete _mem;
			_mem = nullptr;
		}
	}

	inline _Offset_Ptr<DWORD> get_ptr() const noexcept { return _ptr; }
	inline size_t get_nop_bytes() const noexcept { return _nop_bytes; }

	inline signature& set_ptr(const _Offset_Ptr<DWORD>& _Ptr) noexcept { _ptr = _Ptr; return *this; }
	inline signature& set_nop_bytes(size_t _BytesNopCount) noexcept { _nop_bytes = _BytesNopCount; return *this; }

private:
	_Offset_Ptr<DWORD> _ptr;
	size_t _nop_bytes;
	static Memory* _mem;
};