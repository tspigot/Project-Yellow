#include "PlayState.h"
#include <SDL_ttf.h>
#include "colors.h"
#include "FontManager.h"
#include "Game.h"
#include "Screen.h"
#include "Map.h"
#include "ImageManager.h"
#include "TextSprite.h"
#include "Tile.h"

#include <functional>

PlayState::PlayState(Game *g) :
	GameState(g)
{
	SDL_Rect dim = g->get_screen()->get_dimensions();
	//SDL_Surface *s = TTF_RenderText(FontManager::inst().get("Lato-reg.ttf 32"), "You are now playing the game", WHITE, BLACK);
	Sprite *spr = new TextSprite(FontManager::inst().get("Lato-reg.ttf 32"), "You are now playing the game", WHITE, BLACK, dim.w / 2, dim.h / 2, Sprite::Anchor::ANCHOR_CENTER);
	this->sprites.push_back(spr);
	map = new Map(g->get_screen(), "map.lua");
	map->init();
	//map->get_tile(make_tile_coords(4,4))->type = Tile::Type::TILE_BLOCKING;
	//map->get_tile(make_tile_coords(3,5))->type = Tile::Type::TILE_BLOCKING;

	spr = new Sprite(ImageManager::inst().get("unit.png"), 0, 0);
	Unit *u = new Unit(spr, map, GroundMovementType::get(), 0, 0);
	units.push_back(u);
	spr = new Sprite(*spr);
	u = new Unit(spr, map, GroundMovementType::get(), 3, 3);
	units.push_back(u);

	this->mouse.x = 0;
	this->mouse.y = 0;

	this->mode = Mode::FREE;

	this->selected = NULL;
}


PlayState::~PlayState(void)
{
	delete map;
	for(Unit *u : units) {
		delete u;
	}
	for(Sprite *s : sprites) {
		delete s;
	}
}

void PlayState::draw_selector(Screen *s) {
	TileCoords selector_coords = get_tile_coords(this->mouse);
	if(selector_coords.x < 0) {
		selector_coords.x = 0;
	} else if(selector_coords.x >= map->get_width()) {
		selector_coords.x = map->get_width()-1;
	}
	if(selector_coords.y < 0) {
		selector_coords.y = 0;
	} else if(selector_coords.y >= map->get_height()) {
		selector_coords.y = map->get_height()-1;
	}
	Sprite selector(ImageManager::inst().get("select.png"), selector_coords.x*BASE_TILE_SIZE, selector_coords.y*BASE_TILE_SIZE);
	selector.draw(s->get_surf());
}

void PlayState::draw(Screen *s) {
	s->clear();
	for(Sprite *spr : sprites) {
		spr->draw(s->get_surf());
	}
	map->draw(s);
	for(Unit *u : units) {
		u->draw(s);
	}
	draw_selector(s);
}

void PlayState::update() {
	for(Unit *u : units) {
		u->update();
	}
}

void PlayState::handle_motion_event(SDL_Event e) {
	SDL_MouseMotionEvent me = e.motion;
	this->mouse.x = me.x;
	this->mouse.y = me.y;
}

void PlayState::handle_free_click(TileCoords tc) {
	//look to see if we clicked a unit
	Unit *u = get_unit_from_tile(tc);
	if(u == NULL) {
		//no unit
	} else { 
		//select unit
		if(this->selected != NULL) {
			this->selected->set_selected(false);
			this->selected = NULL;
		}
		map->unhighlight();
		u->set_selected(true);
		this->selected = u;
		this->mode = Mode::SELECTED;
	}
}

void PlayState::handle_selected_click(TileCoords tc) {
	Unit *u = get_unit_from_tile(tc);
	if(u == NULL) {
		//move unit?
	} else if(u == this->selected) {
		map->unhighlight();
		u->set_selected(false);
		this->selected = NULL;
		this->mode = Mode::FREE;
	} else {
		//switch if unit is ally
		map->unhighlight();
		this->selected->set_selected(false);
		u->set_selected(true);
		this->selected = u;
	}
}

void PlayState::handle_click_event(SDL_Event e) {
	SDL_MouseButtonEvent mbe = e.button;
	int b = mbe.button;
	int x = mbe.x;
	int y = mbe.y;
	ScreenCoords sc;
	sc.x = x;
	sc.y = y;
	TileCoords tc = get_tile_coords(sc);

	switch(this->mode) {
	case FREE:
		handle_free_click(tc);
		break;
	case SELECTED:
		handle_selected_click(tc);
		break;
	}
}

void PlayState::handle_event(SDL_Event e) {
	switch(e.type) {
	case SDL_MOUSEMOTION:
		handle_motion_event(e);
		break;
	case SDL_MOUSEBUTTONDOWN:
		handle_click_event(e);
		break;
	}
}

//converts screen coords to tile coords
TileCoords PlayState::get_tile_coords(ScreenCoords sc) {
	TileCoords result;
	result.x = (sc.x / BASE_TILE_SIZE);
	result.y = (sc.y / BASE_TILE_SIZE);
	return result;
}

Unit *PlayState::get_unit_from_tile(TileCoords tc) {
	for(Unit *u : units) {
		TileCoords uc = u->get_coords();
		if(uc.x == tc.x && uc.y == tc.y) {
			return u;
		}
	}
	return NULL;
}