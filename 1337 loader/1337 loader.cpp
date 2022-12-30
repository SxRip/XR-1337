#include "xr-1337.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include <fstream>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, CHAR* Args, int nCmdShow)
{
	config config;

	if (config.already_created())
	{
		if (!config.open() || !config.update())
			MessageBox(nullptr, "Can't update the config", nullptr, MB_ICONERROR);
	}
	else
		if (!config.create())
			MessageBox(nullptr, "Can't create a config file", nullptr, MB_ICONERROR);

	handle_ptr<CloseHandle> hGame;
	while (!(hGame = GetGameProcessHandle(PROCESS_ALL_ACCESS))) {}

	if (Inject(hGame.get(), config.get_dll().c_str()) != INJECT_STATUS::OK)
		MessageBox(nullptr, "Can't inject the dll in the process", nullptr, MB_ICONERROR);

	return 0;
}