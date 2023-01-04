#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "exception.hpp"
#include <wrl.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class graphics
{
public:

	graphics(const graphics&) = delete;
	graphics operator=(const graphics&&) = delete;

	graphics() = default;
	~graphics();

	graphics(HWND hwnd);

	void create(HWND hwnd);

	void begin() const;

	void end() const;

	void clear(D3DCOLOR color) const;

private:

	Microsoft::WRL::ComPtr<IDirect3D9> _pD3D;
	Microsoft::WRL::ComPtr<IDirect3DDevice9> _pDevice;
};

