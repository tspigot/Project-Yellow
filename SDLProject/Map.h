#pragma once
#include "coords.h"
#include <list>
#include "MovementType.h"

class Screen;
class TileDrawer;
struct Tile;

class Map
{
private:
	Tile **tiles;
	int w, h;
	TileDrawer *tile_drawer;
public:
	Map(int w, int h, Screen *s);
	~Map(void);
	void draw(Screen *s); // scroll parameters?
	Tile *get_tile(TileCoords tc);

	void highlight(TileCoords tc);
	void unhighlight();

	int get_width();
	int get_height();

	std::list<TileCoords> Map::find_neighbors(TileCoords tc);

};

