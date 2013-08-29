#include "EventManager.h"
#include "Game.h"
#include "SDL.h"


EventManager::EventManager(Game *g)
{
	this->game = g;
}

void EventManager::event_loop() {
	bool quit = false; 
	SDL_Event event;

	while(!quit) {
		while(SDL_PollEvent(&event)) {
			if(event.type == SDL_KEYDOWN) {
			}
			else if(event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}
}