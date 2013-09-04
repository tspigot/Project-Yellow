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
#include "LuaInterface.h"

Map::Map(Screen *s, std::string filename)
{
	this->w = -1;
	this->h = -1;
	this->tiles = NULL;
	this->tile_drawer = new TileDrawer(s);
	this->filename = filename;
}


Map::~Map(void)
{
	delete this->tile_drawer;
	for(int i = 0; i < h; i++) {
		delete tiles[i];
	}
	delete tiles;
}

void Map::init() {
	LuaInterface &lua = LuaInterface::get();
	lua.load_file(this->filename);
	lua.call_function("parse", ">");
	lua.call_function("get_width", ">i", &this->w);
	lua.call_function("get_height", ">i", &this->h);
	char *cstr = NULL;
	lua.call_function("get_type_string", ">s", &cstr);
	std::string typestr(cstr);
	delete cstr;
	cstr = NULL;
	std::map<char, TileType&> charmap;

	for(int i = 0; i < typestr.length(); i++) {
		std::string s;
		s += typestr.at(i);
		TileType t;
		lua.call_function("get_tile_type", "s>i", s.c_str(), (int*)&t.type);
		lua.call_function("get_tile_filename", "s>s", s.c_str(), &cstr);
		t.filename = cstr;
		delete cstr;
		this->types.push_back(t);
		charmap[typestr.at(i)] = types.back();
	}
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