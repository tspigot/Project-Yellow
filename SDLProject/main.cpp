#include <SDL.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Log.h"
#include "Screen.h"
#include "Game.h"

SDL_Surface *message = NULL;

TTF_Font *font = NULL;

SDL_Color text = {255, 255, 255};
SDL_Event event;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *dest) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, dest, &offset);
}

bool load_files() {
	font = TTF_OpenFont("lazy.ttf", 28);
	return font != NULL;
}

bool init() {
	Log::init(Log::LOG_LEVEL_DEBUG);
	Log::Infof("Starting program");

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		Log::Errorf("Error initializing SDL: %s", SDL_GetError());
		return false;
	}
	if(IMG_Init(IMG_INIT_PNG) == 0) {
		Log::Errorf("Error initializing image support: %s", IMG_GetError());
		return false;
	}
	if(TTF_Init() == -1) {
		Log::Errorf("Error initializing TrueType fonts: %s", TTF_GetError());
		return false;
	}

	return true;
}

void clean_up() {
	SDL_FreeSurface(message);
	SDL_Quit();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR lpCmdLine,
	int nShowCommand) {
	if(!init()) {
		Log::Errorf("Error initializing game");
		return 1;
	}
	Game *g = new Game(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	g->init_screen();

	Log::Infof("Game starting");

	g->start();

	delete g;
	clean_up();

	return 0;
}