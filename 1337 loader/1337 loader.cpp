#include "xr-1337.hpp"
#include "config.hpp"
#include "window.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, CHAR* Args, int nCmdShow)
{
	window wnd(500, 500, "[XR-1337] LOADER (CREATED BY SXRIR)");

	config config;

	if (config.already_created())
	{
		if (!config.open() || !config.update())
			MessageBox(nullptr, "Can't update the config", nullptr, MB_ICONERROR);
	}
	else
		if (!config.create())
			MessageBox(nullptr, "Can't create a config file", nullptr, MB_ICONERROR);

	bool no_closed = true;

	MSG msg;
	while (no_closed)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return 0;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		wnd.begin();

		ImGui::SetNextWindowPos({});
		ImGui::SetNextWindowSize({ wnd.get_x(), wnd.get_y() });

		if (ImGui::Begin(wnd.get_name(), &no_closed, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
			ImGui::Button("1337 loader");
		ImGui::End();

		wnd.end();
	}


	//handle_ptr<CloseHandle> hGame;
	//while (!(hGame = GetGameProcessHandle(PROCESS_ALL_ACCESS))) {}

	//if (Inject(hGame.get(), config.get_dll().c_str()) != INJECT_STATUS::OK)
	//	MessageBox(nullptr, "Can't inject the dll in the process", nullptr, MB_ICONERROR);

	return 0;
}