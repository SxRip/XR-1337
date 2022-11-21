#include "include/ConsoleMessages.h"
#include "xr-1337.hpp"
#include <fstream>

INJECT_DATA GetDllNameToInject()
{
	std::ifstream config("config.ini");
	if (!config.is_open())
		return {};

	INJECT_DATA inject_data;

	std::string buff;
	while (!config.eof())
	{
		config >> buff;
		if (buff == "METHOD]")
		{
			config >> buff;
			inject_data.inject_method = buff;
		}

		if (buff == "NAME]")
		{
			config >> buff;
			inject_data.dll_name = buff;
		}
	}
	return inject_data;
}

int main()
{
	SetConsoleTitle("1337 LOADER");

	INJECT_DATA inject_data;
	bool is_created = false;

	if (!std::filesystem::exists("config.ini"))
	{
		if (!create_config(inject_data))
		{
			ColoredMessage("Can't create the config file!", MsgColor::LRED, true);
			Sleep(5000);
			return -2;
		}
		is_created = true;
	}

	if (!is_created)
		inject_data = GetDllNameToInject();

	std::filesystem::path extension = inject_data.dll_name;
	if (extension.extension().string().empty())
		inject_data.dll_name.append(".dll");


	std::string simple_dllname = inject_data.dll_name;
	inject_data.dll_name = GetFullPathNear(inject_data.dll_name.c_str());

	if (!std::filesystem::exists(inject_data.dll_name))
	{
		ColoredMessage("The cheat file wasn't found!", MsgColor::LRED, true);
		Sleep(5000);
		return -2;
	}

	const auto slash_animation = [](size_t _Delay)
	{
		std::cout << "\b\\" << std::flush;
		Sleep(_Delay);

		std::cout << "\b|" << std::flush;
		Sleep(_Delay);

		std::cout << "\b/" << std::flush;
		Sleep(_Delay);

		std::cout << "\b-" << std::flush;
		Sleep(_Delay);
	};

	std::cout << "\n\n\tThe dll to inject: "; ColoredMessage(simple_dllname.c_str(), LRED, true);
	std::cout << "\n\tWaiting for a client: "; ColoredMessage("xrEngine.exe  ", MsgColor::LYELLOW);
	//ColoredMessage("\n\tPress SPACE to change injection method", LYELLOW, true);

	handle_ptr<CloseHandle> hGame;
	while (!(hGame = GetGameProcessHandle(PROCESS_ALL_ACCESS)))
		slash_animation(50);

	system("cls");

	ColoredMessage("\n\tInjecting...", LYELLOW, true);
	if (Inject(hGame.get(), inject_data.dll_name.c_str()) != INJECT_STATUS::OK)
	{
		ColoredMessage("\n\tError injecting!", LRED, true);
		Sleep(5000);
		return -3;
	}

	ColoredMessage("\n\tInjected!", MsgColor::LGREEN, true);
	Sleep(5000);
	return 0;
}