#pragma once
#include <SDL.h>

class Button
{
private:
	SDL_Rect box;
public:
	Button(int x, int y, int w, int h);
	void handle_events(SDL_Event e);
	void show(SDL_Surface *screen);
};

