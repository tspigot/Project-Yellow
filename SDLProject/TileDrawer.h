#pragma once
#include <string>
class Screen;
struct Tile;
struct SDL_Surface;

class TileDrawer
{
private:
	std::string get_tile_image_name(Tile *t);
public:
	TileDrawer(Screen *s);
	~TileDrawer();
	void draw_tile(Screen *s, Tile *t, int x, int y);
};

