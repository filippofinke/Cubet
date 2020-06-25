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
	enum                            // static entity types
	{
		NOTUSED = 0,                // entity slot not in use in map (usually seen at deleted entities)
		LIGHT,                      // lightsource, attr1 = radius, attr2 = intensity (or attr2..4 = r-g-b)
		PLAYERSTART,                // attr1 = angle, attr2 = team
		I_CLIPS, I_AMMO, I_GRENADE, // attr1 = elevation
		I_HEALTH, I_HELMET, I_ARMOUR, I_AKIMBO,
		MAPMODEL,                   // attr1 = angle, attr2 = idx, attr3 = elevation, attr4 = texture, attr5 = pitch, attr6 = roll
		CARROT,                     // attr1 = tag, attr2 = type
		LADDER,                     // attr1 = height
		CTF_FLAG,                   // attr1 = angle, attr2 = red/blue
		SOUND,                      // attr1 = idx, attr2 = radius, attr3 = size, attr4 = volume
		CLIP,                       // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height, attr6 = slope, attr7 = shape
		PLCLIP,                     // attr1 = elevation, attr2 = xradius, attr3 = yradius, attr4 = height, attr6 = slope, attr7 = shape
		DUMMYENT,                   // temporary entity without any function - will not be saved to map files, used to mark positions and for scripting
		MAXENTTYPES
	};

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