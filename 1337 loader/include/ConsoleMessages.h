#pragma once
#include <Windows.h>
#include <iostream>

enum MsgColor
{
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = 6,

	LRED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	LGREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LBLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LYELLOW = 6 | FOREGROUND_INTENSITY,
};

void ColoredMessage(const char* _Msg, unsigned int _dwColor, bool _Endl = false)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStd == INVALID_HANDLE_VALUE)
		return;

	SetConsoleTextAttribute(hStd, _dwColor);

	std::cout << _Msg << (_Endl ? '\n' : '\0');

	SetConsoleTextAttribute(hStd, 7);

	//CloseHandle(hStd);
}