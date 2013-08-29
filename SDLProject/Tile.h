#pragma once
struct Tile
{
	enum Type {
		TILE_EMPTY,
		TILE_BLOCKING
	};
	Type type;
	bool highlighted;
};

