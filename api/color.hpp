#pragma once
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

class color {
public:
#ifndef _WIN32
	static const int red = 31;
	static const int yellow = 33;
	static const int silver = 30;
	static const int white = 37;
	static const int def = 39;
#else
	static const int def = 7;
	static const int red = 12;
	static const int yellow = 14;
	static const int silver = 8;
	static const int white = 15;
#endif
	static void set(int color)
	{
#ifndef _WIN32
		std::cout << "\033[1;" << color << "m";
#else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
	}
};
