#include "Cubet.h"
#include "Logger.h"
#include "Offsets.h"
#include "Hooks.h"

#pragma region Static variables
HMODULE Cubet::m_Module = NULL;
uintptr_t Cubet::m_GameBase = NULL;
#pragma endregion

#pragma region Static methods
void Cubet::Start(HMODULE module)
{
	LOG_DEBUG("%s", __FUNCTION__);
	m_Module = module;
	m_GameBase = (uintptr_t)GetModuleHandleA(NULL);

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

	return 0;
}

void Cubet::Stop()
{
	LOG_DEBUG("%s", __FUNCTION__);
	FreeLibraryAndExitThread(m_Module, 0);
}
#pragma endregion
