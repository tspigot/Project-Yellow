#pragma once
#include <SDL.h>

class Screen;
class Game;

class GameState
{
protected:
	Game *game;
public:
	GameState(Game *g);
	virtual void draw(Screen *s)=0;
	virtual void update()=0;
	virtual void handle_event(SDL_Event e)=0;
	virtual ~GameState(void);
};

