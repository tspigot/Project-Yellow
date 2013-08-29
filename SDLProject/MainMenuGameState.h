#pragma once
#include "gamestate.h"
#include <list>

class Sprite;

class MainMenuGameState :
	public GameState
{
private:
	void handle_mouse_down(SDL_Event e);
	std::list<Sprite*> sprites;
	int button_pressed;
public:
	MainMenuGameState(Game *g);
	~MainMenuGameState(void);
	virtual void draw(Screen *s) override;
	virtual void update() override;
	virtual void handle_event(SDL_Event e) override;
};

