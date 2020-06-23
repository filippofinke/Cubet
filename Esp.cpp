#include <Windows.h>
#include <gl/GL.h>
#include "Esp.h"
#include "Utils.h"
#include "Cubet.h"
#include "Sdk.h"
#include "Offsets.h"
#include "Logger.h"

void Begin() {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void DrawRect(float x, float y, float x2, float y2) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glRectf(x, y, x2, y2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void End() {
	glEnable(GL_DEPTH_TEST);
}


void Esp::Draw() {
	Begin();

	Player* local = *(Player**)(Cubet::m_GameBase + OFFSET_LOCAL_PLAYER);

	uintptr_t* players = *(uintptr_t**)(Cubet::m_GameBase + OFFSET_PLAYER_LIST);
	int maxPlayers = *(int*)(Cubet::m_GameBase + OFFSET_MAX_PLAYERS);

	const char* gameMode = Gamemode[(*(int*)OFFSET_GAME_MODE) + 1];
	bool teamMode = strstr(gameMode, "team") != nullptr;

	for (int i = 0; i < maxPlayers; i++) {
		Player* p = (Player*)players[i];
		if (p == NULL || p->health <= 0) continue;
		Vector2 headPos, footPos;

		if (Utils::WorldToScreen(p->headPos, headPos) && Utils::WorldToScreen(p->footPos, footPos)) {
			float height = footPos.y - headPos.y;
			float width = height / 2;

			if (teamMode && p->team == local->team) glColor3f(0, 0, 255); // BLUE
			else glColor3f(255, 0, 0); // RED

			DrawRect(headPos.x - width / 2, headPos.y, footPos.x + width, footPos.y);
		}
	}
	End();
}