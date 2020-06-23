#include "Utils.h"
#include "Offsets.h"
#include "Sdk.h"

bool Utils::WorldToScreen(Vector3 pos, Vector2& screen) {

	Screen* size = (Screen*)OFFSET_SCREENSIZE;

	float* matrix = (float*)OFFSET_VIEWMATRIX;

	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (size->width / 2 * NDC.x) + (NDC.x + size->width / 2);
	screen.y = -(size->height / 2 * NDC.y) + (NDC.y + size->height / 2);
	return true;

}