#pragma once
#include <Windows.h>

enum class Handles
{
	General,
	File
};

void SafeCloseHandle(HANDLE& handle);
void SafeCloseHandle(HANDLE& handle, const Handles& handleType);