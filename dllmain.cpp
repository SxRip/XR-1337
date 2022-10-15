﻿#include "include/Memory.hpp"
#include "include/internet.hpp"
#include "include/handles.hpp"
#include "include/processes.hpp"
#include "offsets/offsets.hpp"

/*
*
* В хеадер была добавлена функция позволяющая получить ключ из pastebin
*
*/


void WINAPI Main(HMODULE hModule)
{
	Offsets offsets(MOD::StalkerNET);
	Memory mem;

	while (true)
	{
		if (GetAsyncKeyState(VK_END))
			break;

		float* pStamina = mem.get_pointer<float>(offsets.Actor.Stamina);
		float* pHP = mem.get_pointer<float>(offsets.Actor.HP);
		float* pWeight = mem.get_pointer<float>(offsets.Actor.Weight);
		float* pCrosshairDelayInfo = mem.get_pointer<float>(offsets.Actor.Crosshair.DelayInfo);
	
		const char* pActorName = mem.get_pointer<const char>(offsets.Actor.Name);

		int* pTargetType = mem.get_pointer<int>(offsets.Actor.Crosshair.TargetType);
		int* pMoney = mem.get_pointer<int>(offsets.Actor.Money);
		bool* pWeaponSelected = mem.get_pointer<bool>(offsets.Actor.Weapon.IsInHands);


		if (pStamina)
			*pStamina = 1;

		if (pWeight)
			*pWeight = 0;

		if (pMoney)
			*pMoney = 100000;


		if (pWeaponSelected && *pWeaponSelected)
			if (pTargetType &&
				*pTargetType == TargetType::Alive && GetForegroundWindowName() == "xrEngine.exe")
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}

		if (pCrosshairDelayInfo)
			*pCrosshairDelayInfo = 1;
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

