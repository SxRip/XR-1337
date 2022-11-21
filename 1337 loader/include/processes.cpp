#include "processes.hpp"

bool KillProcess(const std::string& processName)
{
	handle_ptr<CloseHandle> hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hSnap)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap.get(), &pe))
		if (pe.szExeFile == processName)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,
				false, pe.th32ProcessID);

			if (!hProcess)
				return false;

			if (TerminateProcess(hProcess, 0))
				return true;
		}
	return false;
}

bool ProcessIsRunning(const std::string& processName)
{
	handle_ptr<CloseHandle> hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hSnap)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap.get(), &pe))
		if (pe.szExeFile == processName)
			return true;

	return false;
}

std::string GetForegroundWindowName()
{
	HWND hwnd = GetForegroundWindow();
	if (!hwnd)
		return "";

	DWORD pID;
	GetWindowThreadProcessId(hwnd, &pID);

	handle_ptr<CloseHandle> hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pID);
	if (!hProcess)
		return "";

	char cProcess[MAX_PATH];
	if (!QueryFullProcessImageName(hProcess.get(), NULL, cProcess, &pID))
		return "";

	std::string process = cProcess;
	process = process.substr(process.find_last_of("\\") + 1);
	return process;
}

DWORD GetProcessID(const std::string& processName)
{
	handle_ptr<CloseHandle> hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hSnap)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap.get(), &pe))
		if (pe.szExeFile == processName)
			return pe.th32ProcessID;
	return false;
}

HANDLE GetHandleByHWND(HWND hWindow, DWORD dwDesiredAccess)
{
	DWORD pID;
	GetWindowThreadProcessId(hWindow, &pID);

	return OpenProcess(dwDesiredAccess, false, pID);
}