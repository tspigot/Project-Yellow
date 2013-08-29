#pragma once
#include <SDL.h>

class Screen
{
private:
	int width;
	int height;
	int depth;
	SDL_Surface *surf;
public:
	Screen(int w, int h, int d);
	bool init();
	virtual ~Screen(void);
	SDL_Surface *get_surf();
	bool flip();
	SDL_Rect get_dimensions();
	void clear();
};

