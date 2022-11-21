#pragma once
#include <Windows.h>

template <BOOL(__stdcall* _CloseHandle)(HANDLE)>
class handle_ptr
{
public:
	handle_ptr() = default;
	handle_ptr(HANDLE handle) : _Handle{ handle }
	{}

	~handle_ptr()
	{
		if (_Handle)
		{
			_CloseHandle(_Handle);
			_Handle = nullptr;
		}
	}

	inline handle_ptr& operator=(HANDLE handle) noexcept
	{
		_Handle = handle;
		return *this;
	}

	inline operator bool() const noexcept
	{
		return _Handle != nullptr && _Handle != INVALID_HANDLE_VALUE;
	}

	inline bool operator==(handle_ptr& _Right) noexcept { return _Handle == _Right.get(); }

	HANDLE& get() noexcept { return _Handle; }

	handle_ptr& close() noexcept { _CloseHandle(_Handle); _Handle = nullptr; return *this; }

private:
	HANDLE _Handle;
};