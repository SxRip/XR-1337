#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <Windows.h>
#include <exception>

#pragma comment(lib, "d3d9.lib")

#define VERIFY(call) if(!call) throw std::exception("error")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

	window(const window&) = delete;
	window operator=(const window&&) = delete;

	window(int x, int y, const char* name);

	static LRESULT CALLBACK WndMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK WndHandleThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	LRESULT CALLBACK WndMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

private:
	_window_class _class;

	HWND _hwnd;
};

