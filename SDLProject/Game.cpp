#include "Game.h"
#include "Screen.h"
#include "GameState.h"
#include <SDL.h>
#include "MainMenuGameState.h"

Game::Game(int w, int h, int d) 
{
	this->screen = new Screen(w,h,d);
	this->state = new MainMenuGameState(this);
	this->next = NULL;
}

Game::~Game(void)
{
	delete this->state;
	delete this->screen;
}

Screen *Game::get_screen() {
	return screen;
}

bool Game::init_screen() {
	return this->screen->init();
}

void Game::start() {
	bool quit=false;
	SDL_Event event;
	while(!quit) {
		if(next != NULL) {
			delete this->state;
			this->state = this->next;
			this->next = NULL;
		}
		state->update();
		state->draw(screen);
		screen->flip();
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quit = true;
			}
			state->handle_event(event);
		};
	}
}

void Game::set_next(GameState *gs) {
	this->next = gs;
}