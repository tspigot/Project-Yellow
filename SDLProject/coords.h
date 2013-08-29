#pragma once

struct _Coords {
	int x, y;
};

struct TileCoords : public _Coords {};
struct ScreenCoords : public _Coords {};

TileCoords make_tile_coords(int x, int y);