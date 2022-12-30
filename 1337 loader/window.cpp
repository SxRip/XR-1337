#include "window.hpp"

window::window(int x, int y, const char* name) : _class{ GetModuleHandle(nullptr), "Loader" }
{
	RECT rc{ 0, 0, x, y };

	VERIFY(AdjustWindowRect(&rc, WS_POPUP, false));

	int centerX = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	int centerY = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

	_hwnd = CreateWindow(_class.get_class(), name, WS_POPUP, centerX,
		centerY, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, _class.get_instance(), this);

	VERIFY(_hwnd);

	ShowWindow(_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(_hwnd);
}

LRESULT window::WndMsgSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		case WM_NCCREATE:
		{
			CREATESTRUCT* pData = reinterpret_cast<CREATESTRUCT*>(lParam);

			window* pWindow = static_cast<window*>(pData->lpCreateParams);

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG>(pWindow->_hwnd));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG>(&WndHandleThunk));

			pWindow->WndMsgProc(hwnd, msg, wParam, lParam);
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT window::WndHandleThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	window* pWindow = reinterpret_cast<window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return pWindow->WndMsgProc(hwnd, msg, wParam, lParam);
}

LRESULT window::WndMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

window::_window_class::_window_class(HINSTANCE hInstance, const char* class_name) : _hInst{ hInstance }, _name{ class_name }
{
	wc.lpfnWndProc = WndMsgSetup;
	wc.hInstance = hInstance;
	wc.lpszClassName = class_name;

	VERIFY(RegisterClassEx(&wc));
}
