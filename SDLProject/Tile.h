#pragma once
#include <string>

struct TileType 
{
	enum MoveType {
		TILE_EMPTY=0,
		TILE_BLOCKING=1
	};
	MoveType type;
	std::string filename;
};

struct Tile
{
	const TileType &t;
	bool highlighted;
	Tile(const TileType &t);
};
