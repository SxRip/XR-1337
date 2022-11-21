#pragma once
#include "handles.hpp"
#include <TlHelp32.h>
#include <string>

bool KillProcess(const std::string& processName);

bool ProcessIsRunning(const std::string& processName);

std::string GetForegroundWindowName();

DWORD GetProcessID(const std::string& processName);

HANDLE GetHandleByHWND(HWND hWindow, DWORD dwDesiredAccess);