#pragma once
#include "GameState.h"
#include <list>
#include "Sprite.h"
#include "Unit.h"
#include "coords.h"

class Map;

class PlayState :
	public GameState
{
private:
	std::list<Sprite*> sprites;
	Map *map;
	std::list<Unit*> units;
	ScreenCoords mouse;

	void handle_free_click(TileCoords tc);
	void handle_selected_click(TileCoords tc);

	void handle_motion_event(SDL_Event e);
	void handle_click_event(SDL_Event e);
	void draw_selector(Screen *s);
	Unit *selected;
	enum Mode {
		FREE,
		SELECTED
	} mode;
public:
	static const int BASE_TILE_SIZE = 64;
	PlayState(Game *g);
	~PlayState(void);

	TileCoords get_tile_coords(ScreenCoords sc);
	
	virtual void draw(Screen *s);
	virtual void update();
	virtual void handle_event(SDL_Event e);
	Unit *get_unit_from_tile(TileCoords tc);
};

