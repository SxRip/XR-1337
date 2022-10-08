#include "processes.hpp"

bool KillProcess(const std::string& processName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap, &pe))
		if (pe.szExeFile == processName)
		{
			SafeCloseHandle(hSnap);

			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,
				false, pe.th32ProcessID);

			if (!hProcess)
				return false;

			if (TerminateProcess(hProcess, 0))
			{
				SafeCloseHandle(hProcess);
				return true;
			}
		}

	SafeCloseHandle(hSnap);
	return false;
}

bool ProcessIsRunned(const std::string& processName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap, &pe))
		if (pe.szExeFile == processName)
		{
			SafeCloseHandle(hSnap);
			return true;
		}

	SafeCloseHandle(hSnap);
	return false;
}

std::string GetForegroundWindowName()
{
	HWND hwnd = GetForegroundWindow();
	if (!hwnd)
		return "";

	DWORD pID;
	GetWindowThreadProcessId(hwnd, &pID);

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pID);
	if (!hProcess)
		return "";

	char cProcess[MAX_PATH];
	if (!QueryFullProcessImageName(hProcess, NULL, cProcess, &pID))
		return "";
	SafeCloseHandle(hProcess);

	std::string process = cProcess;
	process = process.substr(process.find_last_of("\\") + 1);
	return process;
}

DWORD GetProcessID(const std::string& processName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap, &pe))
		if (pe.szExeFile == processName)
		{
			SafeCloseHandle(hSnap);

			return pe.th32ProcessID;
		}

	SafeCloseHandle(hSnap);
	return false;
}

HANDLE GetHandleByHWND(HWND hWindow, DWORD dwDesiredAccess)
{
	DWORD pID;
	GetWindowThreadProcessId(hWindow, &pID);

	HANDLE hProcess = OpenProcess(dwDesiredAccess, false, pID);
	if (!hProcess)
		return nullptr;

	return hProcess;
}