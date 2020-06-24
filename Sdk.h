#pragma once
#include <cstdint>
#include <Windows.h>

typedef unsigned char uchar;

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;
};

struct Vector4 {
	float x, y, z, w;
};

static const char* Gamemode[] =
{
	"demo playback",
	"team deathmatch", "coopedit", "deathmatch", "survivor",
	"team survivor", "capture the flag team", "pistol frenzy", "bot team deathmatch", "bot deathmatch", "last swiss standing",
	"one shot, one kill", "team one shot, one kill", "bot one shot, one kill", "hunt the flag team", "team keep the flag",
	"keep the flag", "team pistol frenzy", "team last swiss standing", "bot pistol frenzy", "bot last swiss standing", "bot team survivor", "bot team one shot, one kill"
};

class Player
{
public:
	char pad_0000[4]; //0x0000
	Vector3 headPos; //0x0004
	char pad_0010[36]; //0x0010
	Vector3 footPos; //0x0034
	Vector2 angles; //0x0040
	char pad_0048[176]; //0x0048
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[293]; //0x0100
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t team; //0x032C
};

class Entity
{
public:
	short x; //0x0000 
	short y; //0x0002 
	short z; //0x0004 
	short attr1; //0x0006 
	BYTE type; //0x0008 
	BYTE attr2; //0x0009 
	BYTE attr3; //0x000A 
	BYTE attr4; //0x000B 
	BYTE spawned; //0x000C 
	char pad_0x000D[0x3]; //0x000D
	int lastmillis; //0x0010 
};


class EntityList
{
public:

	class List
	{
	public:
		Entity entities[1024];
	};

	List* list; //0x0000 
	int32_t max; //0x0004 
	int32_t count; //0x0008 

};

struct Screen {
	int32_t width;
	int32_t height;
};