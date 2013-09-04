#include "TileDrawer.h"
#include "Screen.h"
#include "Tile.h"
#include "ImageManager.h"
#include "Sprite.h"
#include "SDL_rotozoom.h"
#include "Log.h"

TileDrawer::TileDrawer(Screen *s) {
}

TileDrawer::~TileDrawer() {
}

std::string TileDrawer::get_tile_image_name(Tile *t) {
	/*
	switch(t->type) {
	case Tile::Type::TILE_EMPTY:
		return std::string("tile-empty.png");
	case Tile::Type::TILE_BLOCKING:
		return std::string("tile-blocking.png");
	default:
		return std::string("");
	}
	*/
	return "";
}

void TileDrawer::draw_tile(Screen *s, Tile *t, int x, int y) {
	std::string image_name = get_tile_image_name(t);
	SDL_Surface *surf = ImageManager::inst().get(image_name);
	SDL_Surface *tblue = ImageManager::inst().get("tblue.png");
	if(surf != NULL) {
		Sprite spr(surf, x, y);
		spr.draw(s->get_surf());
		if(t->highlighted) {
			Sprite highlight(tblue, x, y);
			highlight.draw(s->get_surf());
		}
	}
}
