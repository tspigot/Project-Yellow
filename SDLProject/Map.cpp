#include "Map.h"
#include <SDL.h>
#include "TileDrawer.h"
#include "Tile.h"
#include "PlayState.h"
#include "Log.h"
#include <queue>
#include <math.h>
#include <set>
#include <map>

Map::Map(int w, int h, Screen *s)
{
	this->w = w;
	this->h = h;
	tiles = new Tile*[h];
	for(int i = 0; i < h; i++) {
		tiles[i] = new Tile[w];
		for(int j = 0; j < w; j++) {
			tiles[i][j].type = Tile::Type::TILE_EMPTY;
			tiles[i][j].highlighted = false;
		}
	}
	this->tile_drawer = new TileDrawer(s);
}


Map::~Map(void)
{
	delete this->tile_drawer;
	for(int i = 0; i < h; i++) {
		delete tiles[i];
	}
	delete tiles;
}

Tile *Map::get_tile(TileCoords tc) {
	int x = tc.x, y = tc.y;
	if(x >= w || x < 0 || y >= h || y < 0) {
		return NULL;
	}
	return &tiles[y][x];
}

void Map::draw(Screen *s) {
	TileCoords tc;
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			tc.x = j;
			tc.y = i;
			tile_drawer->draw_tile(s, get_tile(tc), (int)(PlayState::BASE_TILE_SIZE)*j, (int)(PlayState::BASE_TILE_SIZE)*i);
		}
	}
}

int Map::get_width() { return this->w; }
int Map::get_height() { return this->h; }

void Map::highlight(TileCoords tc) {
	Tile *t = get_tile(tc);
	if(t == NULL) {
		Log::Infof("Highlighted nonexistent tile");
	} else {
		t->highlighted = true;
	}
}

void Map::unhighlight() {
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			tiles[i][j].highlighted = false;
		}
	}
}

std::list<TileCoords> Map::find_neighbors(TileCoords tc) {
	int w = this->get_width();
	int h = this->get_height();
	std::list<TileCoords> coords;
	if(tc.x != 0) {
		TileCoords c;
		c.x = tc.x - 1;
		c.y = tc.y;
		coords.push_back(c);
	}
	if(tc.y != 0) {
		TileCoords c;
		c.x = tc.x;
		c.y = tc.y - 1;
		coords.push_back(c);
	}
	if(tc.x != w-1) {
		TileCoords c;
		c.x = tc.x + 1;
		c.y = tc.y;
		coords.push_back(c);
	}
	if(tc.y != h-1) {
		TileCoords c;
		c.x = tc.x;
		c.y = tc.y + 1;
		coords.push_back(c);
	}
	return coords;
}