#include "offsets/offsets.h"
#include "include/handles.hpp"
#include "Memory.hpp"
#include "include/processes.hpp"

void WINAPI Main(HMODULE hModule)
{
	Offsets offsets;
	Memory mem;

	while (true)
	{
		if (GetAsyncKeyState(VK_END))
			break;

		std::vector<DWORD> CrosshairTargetExists{ 0x992D4, 0x4C, 0x14 };
		std::vector<DWORD> CrosshairDelayInfo{ 0x992D4, 0x4C, 0x4 };

		float* pWeight = mem.get_pointer<float>(offsets.ActorWeight);
		float* pStamina = mem.get_pointer<float>(offsets.ActorStamina);
		int* pMoney = mem.get_pointer<int>(offsets.ActorMoney);
		const char* name = mem.get_pointer<const char>(offsets.ActorName);
		float* pCrosshair = mem.get_pointer<float>(CrosshairTargetExists, "xrEngine.exe");
		float* pCrosshairInfo = mem.get_pointer<float>(CrosshairDelayInfo, "xrEngine.exe");

		if (pStamina)
			*pStamina = 1;

		if (pWeight)
			*pWeight = 0;

		if (pMoney)
			*pMoney = 100000;

		if (pCrosshair)
		{
			if (*pCrosshair && GetForegroundWindowName() == "xrEngine.exe")
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}

		if (pCrosshairInfo)
			*pCrosshairInfo = 1;

		Sleep(1);
	}

	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
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
		SafeCloseHandle(hThread);
	}
	}

	return TRUE;
}

