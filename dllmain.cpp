#include "offsets/offsets.h"
#include "include/handles.hpp"
#include "Memory.hpp"

void WINAPI Main(HMODULE hModule)
{
	Offsets offsets;
	Memory mem;

	while (true)
	{
		if (GetAsyncKeyState(VK_END))
			break;

		float* pWeight = mem.get_pointer<float>(offsets.ActorWeight);
		float* pStamina = mem.get_pointer<float>(offsets.ActorStamina);
		int* pMoney = mem.get_pointer<int>(offsets.ActorMoney);
		const char* name = mem.get_pointer<const char>(offsets.ActorName);

		if (pStamina)
			*pStamina = 1;

		if (pWeight)
			*pWeight = 0;

		if (pMoney)
			*pMoney = 100000;

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

