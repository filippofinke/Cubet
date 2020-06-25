#include "Cubet.h"
#include "Logger.h"
#include "Offsets.h"
#include "Hooks.h"

#pragma region Static variables
HMODULE Cubet::Module = NULL;
uintptr_t Cubet::GameBase = NULL;
bool Cubet::Esp = false;
bool Cubet::Aimbot = false;
#pragma endregion

#pragma region Static methods
void Cubet::Start(HMODULE module)
{
	LOG_DEBUG("%s", __FUNCTION__);
	Module = module;
	GameBase = (uintptr_t)GetModuleHandleA(NULL);

	bool hook = Hooks::Hook_SDL_GL_SwapBuffers();
	if (!hook) {
		LOG_FATAL("%s - Hooks::Hook_SDL_GL_SwapBuffers failed: %d", __FUNCTION__, GetLastError());
		ExitProcess(0);
	}

	HANDLE thread = CreateThread(NULL, NULL, &Loop, NULL, NULL, NULL);
	if (!thread) {
		LOG_FATAL("%s - CreateThread failed: %d", __FUNCTION__, GetLastError());
		ExitProcess(0);
	}
}

DWORD APIENTRY Cubet::Loop(LPVOID lparam)
{
	LOG_DEBUG("%s", __FUNCTION__);
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			Esp = !Esp;
			LOG_DEBUG("Esp: %s", (Esp) ? "Enabled" : "Disabled");
		} else if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			Aimbot = !Aimbot;
			LOG_DEBUG("Aimbot: %s", (Aimbot) ? "Enabled" : "Disabled");
		}
		Sleep(10);
	}
	return 0;
}

void Cubet::Stop()
{
	LOG_DEBUG("%s", __FUNCTION__);
	FreeLibraryAndExitThread(Module, 0);
}
#pragma endregion
