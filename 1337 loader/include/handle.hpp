#pragma once
#include <Windows.h>

template <BOOL(__stdcall* _CloseHandle)(HANDLE)>
class handle_ptr
{
public:
	handle_ptr() = default;
	handle_ptr(HANDLE& handle) : _Handle{ &handle } {}

	handle_ptr(HANDLE&& handle) : handle_ptr(handle)
	{}

	~handle_ptr()
	{
		_VERIFY();
	}
	
	inline handle_ptr& operator=(HANDLE& handle) noexcept
	{
		_VERIFY();

		if (handle)
			_Handle = &handle;
		return *this;
	}

	inline handle_ptr& operator=(HANDLE&& handle) noexcept
	{
		return this->operator=(handle);
	}

	inline handle_ptr& operator=(handle_ptr& ptr_handle) noexcept
	{
		_VERIFY();

		if (ptr_handle._Handle)
			_Handle = &*ptr_handle._Handle;

		return *this;
	}

	inline handle_ptr& operator=(handle_ptr&& ptr_handle) noexcept
	{
		return this->operator=(ptr_handle);
	}

	inline operator bool() const noexcept
	{
		return _Handle && *_Handle != INVALID_HANDLE_VALUE;
	}

	inline bool operator==(handle_ptr& _Right) const noexcept { return *_Handle == *_Right._Handle; }

	HANDLE get() const noexcept { return _Handle ? *_Handle : nullptr; }

	handle_ptr& close() noexcept
	{
		_VERIFY();
		return *this;
	}

private:

	void _VERIFY() noexcept
	{
		if (_Handle && *_Handle)
		{
			_CloseHandle(*_Handle);
			*_Handle = nullptr;
		}

		_Handle = nullptr;
	}

	HANDLE* _Handle;
};