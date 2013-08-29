#pragma once
#include <SDL.h>

class Sprite
{
public:
	enum Anchor {
		ANCHOR_TOPLEFT,
		ANCHOR_CENTER,
		ANCHOR_BOTTOMCENTER
	};
	int x, y;
	
protected:
	SDL_Surface *surf;
	SDL_Rect get_anchored_bounds();
	Anchor anchor;
public:
	Sprite(SDL_Surface *surf, int x, int y, Anchor a=ANCHOR_TOPLEFT);
	virtual ~Sprite(void);
	void draw(SDL_Surface *target);
	bool contains(int x, int y);
};