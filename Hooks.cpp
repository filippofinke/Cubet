#include "Hooks.h"
#include "Offsets.h"
#include "Logger.h"
#include "Esp.h"
#include "Cubet.h"
#include "Aimbot.h"

SDL_GL_SwapBuffers Hooks::m_SDL_GL_SwapBuffers = nullptr;

void Hooks::Hooked_SDL_GL_SwapBuffers() {
	if(Cubet::Esp) Esp::Draw();
	if (Cubet::Aimbot) Aimbot::Main();
	m_SDL_GL_SwapBuffers();
}

bool Hooks::Hook_SDL_GL_SwapBuffers() {
	LOG_DEBUG("%s", __FUNCTION__);

	DWORD old;
	BOOL status = VirtualProtect((LPVOID)OFFSET_SDL_GL_SWAPBUFFERS, 6, PAGE_EXECUTE_READWRITE, &old);
	if (status == 0) return false;

	// The ptr is a pointer to the exported function from the SDL dll.
	DWORD32 ptr = *(DWORD32*)(OFFSET_SDL_GL_SWAPBUFFERS + 2);
	m_SDL_GL_SwapBuffers = *(SDL_GL_SwapBuffers*)ptr;

	// Converting FF 25 00 00 00 00 to E9 00 00 00 00 90
	memset((LPVOID)OFFSET_SDL_GL_SWAPBUFFERS, 0xE9, 1);
	memset((LPVOID)(OFFSET_SDL_GL_SWAPBUFFERS + 5), 0x90, 1);

	// Patch the jmp instruction
	DWORD32 offset = (DWORD32)Hooked_SDL_GL_SwapBuffers - OFFSET_SDL_GL_SWAPBUFFERS - 5;
	*(DWORD*)(OFFSET_SDL_GL_SWAPBUFFERS + 1) = offset;

	VirtualProtect((LPVOID)OFFSET_SDL_GL_SWAPBUFFERS, 6, old, NULL);
	if (status == 0) return false;

	LOG_DEBUG("%s - Hook applied!", __FUNCTION__);
	return true;
}