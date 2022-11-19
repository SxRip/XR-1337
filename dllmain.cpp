#define STALKERNET
#include "XR-1337/includes/XR-1337.hpp"

void WINAPI Main(HMODULE hModule)
{
	Memory mem;

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	if (!BypassDebugging())
		return false;

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main),
				hModule, 0, nullptr);

			if (!hThread)
			{
				MessageBox(nullptr, "Can't create the thread", nullptr, MB_ICONERROR);
				return -1;
			}
			CloseHandle(hThread);
		}
	}

	return true;
}

