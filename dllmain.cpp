#define STALKERNET

#include "XR-1337/includes/XR-1337.hpp"
#include "include/processes.hpp"

void WINAPI Main(HMODULE hModule)
{
	Memory mem;

	while (!GetAsyncKeyState(VK_END))
	{
		_Offset_Ptr<float> pStamina = mem.get_pointer<float>(offsets::initialized::actor::stamina);
		_Offset_Ptr<float> pHP = mem.get_pointer<float>(offsets::initialized::actor::HP);
		_Offset_Ptr<float> pWeight = mem.get_pointer<float>(offsets::initialized::actor::weight);
		_Offset_Ptr<float> pCrosshairDelayInfo = mem.get_pointer<float>(offsets::initialized::actor::crosshairDelayInfo);
		_Offset_Ptr<float> pFov = mem.get_pointer<float>(offsets::initialized::actor::fov);

		_Offset_Ptr<float> pX = mem.get_pointer<float>(offsets::initialized::actor::coordX);
		_Offset_Ptr<float> pY = mem.get_pointer<float>(offsets::initialized::actor::coordY);
		_Offset_Ptr<float> pZ = mem.get_pointer<float>(offsets::initialized::actor::coordZ);

		_Offset_Ptr<const char> pActorName = mem.get_pointer<const char>(offsets::initialized::actor::name);

		_Offset_Ptr<size_t> pActorFireState = mem.get_pointer<size_t>(offsets::initialized::actor::fireState);
		_Offset_Ptr<size_t> pTargetType = mem.get_pointer<size_t>(offsets::initialized::actor::targetType);

		_Offset_Ptr<int> pMoney = mem.get_pointer<int>(offsets::initialized::actor::money);

		_Offset_Ptr<bool> pWeaponInHands = mem.get_pointer<bool>(offsets::initialized::actor::weaponIsInHands);

		pStamina = 1;

		pWeight = 0;

		if (*pMoney < 1000000)
			pMoney += 100000;

		if (pWeaponInHands)
			if (pTargetType == game::target_type::alive)
				if (pActorFireState == game::fire_state::can_shoot)
					if (GetForegroundWindowName() == "xrEngine.exe")
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

