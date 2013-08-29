#include "Sprite.h"

Sprite::Sprite(SDL_Surface *surf, int x, int y, Sprite::Anchor a)
{
	this->surf = surf;
	this->x = x;
	this->y = y;
	this->anchor = a;
}


Sprite::~Sprite(void)
{
}

SDL_Rect Sprite::get_anchored_bounds() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	switch(this->anchor) {
	case Sprite::Anchor::ANCHOR_CENTER:
		rect.x -= (surf->w)/2;
		rect.y -= (surf->h)/2;
		break;
	case Sprite::Anchor::ANCHOR_BOTTOMCENTER:
		rect.x -= (surf->w)/2;
		rect.y -= (surf->h);
		break;
	default:
		break;
	}
	return rect;
}

void Sprite::draw(SDL_Surface *target) {
	SDL_Rect rect = get_anchored_bounds();
	SDL_BlitSurface(this->surf, NULL, target, &rect);
}

bool Sprite::contains(int x, int y) {
	SDL_Rect r = get_anchored_bounds();
	return r.x < x && r.y < y && (r.x + r.w) > x && (r.y + r.h) > y;
}