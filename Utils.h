#pragma once
#include "Sdk.h"


class Utils
{
public:
	static bool WorldToScreen(Vector3 pos, Vector2& screen);
	static bool IsVisible(Vector3 from, Vector3 to);
};


