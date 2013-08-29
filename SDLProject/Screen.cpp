#include "Screen.h"
#include <SDL.h>
#include "Log.h"

Screen::Screen(int w, int h, int d)
{
	this->width = w;
	this->height = h;
	this->depth = d;
	this->surf = NULL;
}

Screen::~Screen(void)
{
	if(this->surf != NULL) {
		SDL_FreeSurface(this->surf);
		this->surf = NULL;
	}
}

bool Screen::init() {
	this->surf = SDL_SetVideoMode(this->width, this->height, this->depth, SDL_SWSURFACE);
	if(this->surf == NULL) {
		Log::Errorf("Error creating screen surface: %s", SDL_GetError());
		return false;
	}
	return true;
}

SDL_Surface *Screen::get_surf() {
	return this->surf;
}

bool Screen::flip() {
	if(SDL_Flip(this->surf) == -1) {
		Log::Errorf("Error flipping screen: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}
	return true;
}

SDL_Rect Screen::get_dimensions() {
	SDL_Rect r;
	r.h = this->height;
	r.w = this->width;
	return r;
}

void Screen::clear() {
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x00, 0x00, 0x00));
}