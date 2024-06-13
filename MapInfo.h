#pragma once
#include <Windows.h>
#include "GameObject.h"
#include "Interaction.h"
#define TILE_SIZE 16
enum class Dungeon_Tiles
{
	Dungeon_Gray,
	Dungeon_Ice,
	Dungeon_Ice2,
	Dungeon_Red,
	Dungeon_Sand,
	Dungeon_Sand2,
	Dungeon_Soil,
	Dungeon_Stone,
	Dungeon_Slime
};

enum class Tile_State
{
	Empty,
	Wall,
	LadderUp,
	LadderDown,
	Light
};

struct TILE_INFO
{
	int frameX, frameY;
};

struct MAP_INFO
{
	MAP_INFO() :
		dungeonTiles{ Dungeon_Tiles::Dungeon_Soil },
		tileInfo{ },
		tileState{ },
		rect{},
		object{},
		mapSizeX{ 20 }, mapSizeY{ 20 } {}
	Dungeon_Tiles dungeonTiles;
	TILE_INFO tileInfo[3][256][256];
	Tile_State tileState[256][256];
	Interaction* object[256][256];
	RECT rect[256][256];
	int mapSizeX, mapSizeY;
};



