#pragma once
#include "coords.h"
#include <functional>
#include "MovementIndex.h"
#include "MovementType.h"

class Screen;
class Sprite;
class PlayState;
class Map;
struct Tile;

class Unit
{
private:
	Sprite *sprite;
	int x,y;
	bool selected;
	Map *map;
	int moves;
	MovementIndex index;
	MovementType &movement_type;
public:
	Unit(Sprite *s, Map *m, MovementType &mt, int x, int y);
	~Unit(void);
	void draw(Screen *s);
	void update();
	void set_coords(int x, int y);
	TileCoords get_coords();
	void set_selected(bool val);
	void range(std::function<void(TileCoords)> func);
};

