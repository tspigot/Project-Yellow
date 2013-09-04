#pragma once
#include "coords.h"
#include <list>
#include "MovementType.h"
#include <map>
#include "Tile.h"
#include <memory.h>

class Screen;
class TileDrawer;

class Map
{
private:
	Tile **tiles;
	int w, h;
	TileDrawer *tile_drawer;
	std::string filename;
	std::list<TileType> types;
public:
	Map(Screen *s, std::string filename);
	~Map(void);
	void draw(Screen *s); // scroll parameters?
	Tile *get_tile(TileCoords tc);

	void init();

	void highlight(TileCoords tc);
	void unhighlight();

	int get_width();
	int get_height();

	std::list<TileCoords> Map::find_neighbors(TileCoords tc);
};

