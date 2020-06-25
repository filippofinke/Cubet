#pragma once
#include <Windows.h>
class Cubet
{
public:
	static HMODULE Module;
	static uintptr_t GameBase;
	static bool Esp;
	static bool Aimbot;
	static DWORD APIENTRY Loop(LPVOID lparam);
	static void Start(HMODULE module);
	static void Stop();
};

