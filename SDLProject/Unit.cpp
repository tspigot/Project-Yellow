#include "Unit.h"
#include "Sprite.h"
#include "Screen.h"
#include "PlayState.h"
#include "Log.h"
#include "ImageManager.h"
#include "Map.h"
#include "Tile.h"

Unit::Unit(Sprite *s, Map *m, MovementType &mt, int x, int y)
	: index(m,mt,make_tile_coords(x,y), 3),
	  movement_type(mt)
{
	this->sprite = s;
	this->map = m;
	this->set_coords(x,y);
	this->set_selected(false);
	this->moves = 3;
	this->index.construct();
}

Unit::~Unit(void)
{
}

void Unit::set_coords(int x, int y) {
	this->x = x;
	this->y = y;
	this->sprite->x = x*PlayState::BASE_TILE_SIZE;
	this->sprite->y = y*PlayState::BASE_TILE_SIZE;
}

void Unit::draw(Screen *s) {
	if(selected) {
		int x = this->sprite->x;
		int y = this->sprite->y;
		SDL_Surface *surf = ImageManager::inst().get("selected.png");
		Sprite spr(surf, x, y);
		spr.draw(s->get_surf());
	}
	this->sprite->draw(s->get_surf());
}

void Unit::update() {
	if(selected) {
		//highlight move range
		this->range([this](TileCoords tc) {
			Tile *t = this->map->get_tile(tc);
			t->highlighted = true;
		});
	}
}

TileCoords Unit::get_coords() {
	TileCoords result;
	result.x = this->x;
	result.y = this->y;
	return result;
}

void Unit::set_selected(bool val) {
	this->selected = val;
}

void Unit::range(std::function<void(TileCoords)> func) {
	index.apply_to_tiles([&func](TileCoords tc) {
		func(tc);
	});
}