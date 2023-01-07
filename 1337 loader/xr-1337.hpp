#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <filesystem>
#include <fstream>
#include "include/processes.hpp"
#include "config.hpp"

std::string stalker_process = "xrEngine.exe";
std::string stalker_dedicated_path = "dedicated";

bool GetGameProcessID(DWORD& dwProcessID)
{
	handle_ptr<CloseHandle> hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (!hSnap)
		return false;

	PROCESSENTRY32 pe{ sizeof(pe) };

	while (Process32Next(hSnap.get(), &pe))
	{
		if (pe.szExeFile == stalker_process)
		{
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, false, pe.th32ProcessID);

			if (!hProcess)
				return false;

			char cPath[MAX_PATH]{};
			if (GetModuleFileNameEx(hProcess, nullptr, cPath, MAX_PATH))
			{
				std::filesystem::path filePath = cPath;

				std::string parentPath = filePath.parent_path().string();

				parentPath = parentPath.substr(parentPath.find_last_of('\\') + 1);
				if (parentPath != stalker_dedicated_path)
				{
					dwProcessID = pe.th32ProcessID;
					return true;
				}
			}
		}
	}
	return false;
}

inline HANDLE GetGameProcessHandle(DWORD dwAccess)
{
	DWORD _ProcessID = 0;
	if (GetGameProcessID(_ProcessID))
		return OpenProcess(dwAccess, false, _ProcessID);

	return nullptr;
}

INJECT_STATUS Inject(HANDLE hGame, const char* cDllPath)
{
	VOID* allocated = VirtualAllocEx(hGame, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (!allocated)
		return INJECT_STATUS::ERROR_MEMORY_ALLOCATION;

	if (!WriteProcessMemory(hGame, allocated, cDllPath, strlen(cDllPath), nullptr))
		return INJECT_STATUS::ERROR_MEMORY_WRITING;

	HANDLE hThread = CreateRemoteThread(hGame, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), allocated, 0, nullptr);

	if (!hThread)
		return INJECT_STATUS::ERROR_CREATING_REMOTE_THREAD;

	CloseHandle(hThread);
	return INJECT_STATUS::OK;
}