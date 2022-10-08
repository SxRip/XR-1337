#include "handles.hpp"

void SafeCloseHandle(HANDLE& handle)
{
	if (handle != nullptr)
	{
		CloseHandle(handle);

		handle = nullptr;
	}
}

void SafeCloseHandle(HANDLE& handle, const Handles& handleType)
{
	if (handle != nullptr)
	{
		switch (handleType)
		{
		case Handles::File:
			FindClose(handle);
			break;

		case Handles::General:
			CloseHandle(handle);
			break;
		}

		handle = nullptr;
	}
}
