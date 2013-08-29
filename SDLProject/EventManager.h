#pragma once

class Game;

class EventManager
{
private:
	Game *game;
public:
	EventManager(Game *g);
	void event_loop();
};

