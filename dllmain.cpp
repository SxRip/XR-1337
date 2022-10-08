// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "offsets/offsets.h"
#include "..\\xrEngine-1337\include\ConsoleMessages.h"

void func()
{
	MessageBox(nullptr, "Hello", nullptr, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	{
		HANDLE hThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(func),
			nullptr, 0, nullptr);

	}
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

