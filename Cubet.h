#pragma once
#include <Windows.h>
class Cubet
{
public:
	static HMODULE m_Module;
	static uintptr_t m_GameBase;
	static DWORD APIENTRY Loop(LPVOID lparam);
	static void Start(HMODULE module);
	static void Stop();
};

