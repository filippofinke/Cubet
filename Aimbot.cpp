#include "Aimbot.h"
#include "Sdk.h"
#include "Cubet.h"
#include "Offsets.h"
#include "Utils.h"
#include <cfloat>
# define M_PI           3.14159265358979323846  /* pi */

Player* GetTarget() {
	Player* local = *(Player**)(Cubet::GameBase + OFFSET_LOCAL_PLAYER);

	uintptr_t* players = *(uintptr_t**)(Cubet::GameBase + OFFSET_PLAYER_LIST);
	int maxPlayers = *(int*)(Cubet::GameBase + OFFSET_MAX_PLAYERS);

	const char* gameMode = Gamemode[(*(int*)OFFSET_GAME_MODE) + 1];
	bool teamMode = strstr(gameMode, "team") != nullptr;

	Player* target = nullptr;
	float closest = FLT_MAX;

	for (int i = 0; i < maxPlayers; i++) {
		Player* p = (Player*)players[i];

		if (p == NULL) continue;

		if (teamMode && p->team == local->team) continue;

		if (p->health <= 0) continue;

		if(!Utils::IsVisible(local->headPos, p->headPos)) continue;

		float dist = p->headPos.Distance(local->headPos);
		if (dist < closest) {
			closest = dist;
			target = p;
		}
	}
	return target;
}

void Aimbot::Main() {
	Player* target = GetTarget();
	if (target != nullptr) {
		Player* local = *(Player**)(Cubet::GameBase + OFFSET_LOCAL_PLAYER);



		Vector3 dst = target->headPos;
		Vector3 src = local->headPos;
		float distance = dst.Distance(src);

		local->angles.x = -atan2f(dst.x - src.x, dst.y - src.y) / (float)M_PI * 180 + 180;
		local->angles.y = asinf((dst.z - src.z) / distance) * 180 / (float)M_PI;
		
	}
}