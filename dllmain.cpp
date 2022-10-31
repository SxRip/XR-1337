#include "include/Memory.hpp"
#include "include/internet.hpp"
#include "include/handles.hpp"
#include "include/processes.hpp"
#include "offsets/offsets.hpp"

void WINAPI Main(HMODULE hModule)
{
	Offsets offsets(MOD::StalkerNET);
	Memory mem;

	_Offset_Ptr<DWORD> StaminaDecInstruction = mem.get_pointer<DWORD>(0xF9461);
	if (!mem.nop(StaminaDecInstruction, 6))
		return;

	while (!GetAsyncKeyState(VK_END))
	{
		_Offset_Ptr<float> pStamina = mem.get_pointer<float>(offsets.Actor.Stamina);
		_Offset_Ptr<float> pHP = mem.get_pointer<float>(offsets.Actor.HP);
		_Offset_Ptr<float> pWeight = mem.get_pointer<float>(offsets.Actor.Weight);
		_Offset_Ptr<float> pCrosshairDelayInfo = mem.get_pointer<float>(offsets.Actor.Crosshair.DelayInfo);
		_Offset_Ptr<float> pFov = mem.get_pointer<float>(offsets.Actor.Camera.Fov);

		/*Added matrix start of a player camera (Exists in ActorCamera (interface))*/
		_Offset_Ptr<float> pX = mem.get_pointer<float>(offsets.Actor.Position.x);
		_Offset_Ptr<float> pY = mem.get_pointer<float>(offsets.Actor.Position.y);
		_Offset_Ptr<float> pZ = mem.get_pointer<float>(offsets.Actor.Position.z);

		_Offset_Ptr<const char> pActorName = mem.get_pointer<const char>(offsets.Actor.Name);

		_Offset_Ptr<int> pTargetType = mem.get_pointer<int>(offsets.Actor.Crosshair.TargetType);
		_Offset_Ptr<int> pMoney = mem.get_pointer<int>(offsets.Actor.Money);

		_Offset_Ptr<bool> pWeaponSelected = mem.get_pointer<bool>(offsets.Actor.Weapon.IsInHands);

		pStamina = 1;

		pWeight = 0;

		pMoney = 100000;

		if (pWeaponSelected)
			if (pTargetType == TargetType::Alive && GetForegroundWindowName() == "xrEngine.exe")
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}

		pCrosshairDelayInfo = 1;
	}

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
		SafeCloseHandle(hThread);
	}
	}

	return true;
}

