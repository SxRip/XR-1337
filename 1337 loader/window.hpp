#pragma once
#include <Windows.h>
#include "exception.hpp"
#include "render.hpp"

class window
{
	class _window_class
	{
	public:
		_window_class(HINSTANCE hInstance = nullptr,
			const char* class_name = nullptr);

		~_window_class() { UnregisterClass(get_class(), _hInst); }

		inline const char* get_class() const noexcept { return _name; }
		inline HINSTANCE get_instance() const noexcept { return _hInst; }

	private:
		HINSTANCE _hInst;
		const char* _name;
		WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	};

public:
	window() = default;
	~window() { if (_hwnd) DestroyWindow(_hwnd); }

	window(const window&) = delete;
	window operator=(const window&&) = delete;

	window(int x, int y, const char* name);

	inline HWND get_window() const noexcept { return _hwnd; }

	void begin() const;
	void end() const;

	inline float get_x() const noexcept { return _x; }
	inline float get_y() const noexcept { return _y; }
	inline const char* get_name() const noexcept { return _name; }

private:
	static LRESULT CALLBACK WndMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK WndHandleThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	LRESULT CALLBACK WndMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	_window_class _class;
	HWND _hwnd;
	render _gfx;

	const char* _name;
	float _x, _y;
};