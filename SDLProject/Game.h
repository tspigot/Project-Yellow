#pragma once

class Screen;
class GameState;

class Game
{
public:
	Game(int w, int h, int bpp);
	~Game(void);
	Screen *get_screen();
	bool init_screen();
	void set_next(GameState *g);

	void start();
private:
	Screen *screen;
	GameState *state;
	GameState *next;
};

