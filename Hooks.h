#pragma once

typedef void (*SDL_GL_SwapBuffers)(void);

class Hooks
{
private:
	static SDL_GL_SwapBuffers m_SDL_GL_SwapBuffers;
	static void Hooked_SDL_GL_SwapBuffers();
public:
	static bool Hook_SDL_GL_SwapBuffers();
};

