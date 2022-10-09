#include "offsets/offsets.h"
#include "include/handles.hpp"
#include <sstream>
#include "Memory.hpp"
#include <vector>

void WINAPI Main(HMODULE hModule)
{
	DWORD dwClientBase = reinterpret_cast<DWORD>(GetModuleHandle("xrGame.dll"));
	Memory mem;

	const std::vector<DWORD> vec{ 0x6ECC04, 0x9D8, 0x114 };

	/*DWORD dwActorCondition = *reinterpret_cast<DWORD*>(dwClientBase + 0x6ECC04);
	DWORD dwActorPTR = *reinterpret_cast<DWORD*>(dwActorCondition + 0x9D8);
	float* pStamina = reinterpret_cast<float*>(dwActorPTR + 0x114);*/

	while (true)
	{
		if (GetAsyncKeyState(VK_END))
			break;

		float* pStamina = mem.get_pointer<float>(vec);

		if (pStamina)
			*pStamina = 1;
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

