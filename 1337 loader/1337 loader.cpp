#include "xr-1337.hpp"
#include "config.hpp"
#include "window.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, CHAR* Args, int nCmdShow)
{
	window wnd(300, 300, "Hello");

	config config;

	if (config.already_created())
	{
		if (!config.open() || !config.update())
			MessageBox(nullptr, "Can't update the config", nullptr, MB_ICONERROR);
	}
	else
		if (!config.create())
			MessageBox(nullptr, "Can't create a config file", nullptr, MB_ICONERROR);





	//handle_ptr<CloseHandle> hGame;
	//while (!(hGame = GetGameProcessHandle(PROCESS_ALL_ACCESS))) {}

	//if (Inject(hGame.get(), config.get_dll().c_str()) != INJECT_STATUS::OK)
	//	MessageBox(nullptr, "Can't inject the dll in the process", nullptr, MB_ICONERROR);

	return 0;
}