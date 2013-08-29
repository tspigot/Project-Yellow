#include <string>
#include <SDL_ttf.h>

#include "MainMenuGameState.h"
#include "Screen.h"
#include "Sprite.h"
#include "FontManager.h"
#include "colors.h"
#include "Log.h"
#include "Game.h"
#include "PlayState.h"
#include "TextSprite.h"

static std::string options[] = {
	"Play",
	"Options",
	"Exit"
};

MainMenuGameState::MainMenuGameState(Game *g)
	: GameState(g)
{
	this->button_pressed = -1;
	TTF_Font *f = FontManager::inst().get("Lato-Reg.ttf 32");
	for(int i = 0; i < 3; i++) {
		//SDL_Surface *s = TTF_RenderText_Shaded(f, options[i].c_str(), WHITE, BLACK);
		Sprite *sprite = new TextSprite(f, options[i].c_str(), WHITE, BLACK, 0, 0, Sprite::Anchor::ANCHOR_CENTER);
		this->sprites.push_back(sprite);
	}
}
 
MainMenuGameState::~MainMenuGameState(void)
{
	for(Sprite *s : sprites) {
		delete s;
	}
	sprites.clear();
}

void MainMenuGameState::draw(Screen *s) {
	for(Sprite *sprite : sprites) {
		sprite->draw(s->get_surf());
	}
}

void MainMenuGameState::update() {
	if(button_pressed != -1) {
		if(button_pressed == 0) {
			game->set_next(new PlayState(game));
			return;
		}
		else if(button_pressed == 2) {
			SDL_Event e;
			e.type = SDL_QUIT;
			SDL_PushEvent(&e);
			return;
		}
	}
	SDL_Rect r = game->get_screen()->get_dimensions();
	int interval = r.h / (sprites.size() + 1);
	int i = 1;
	for(Sprite *sprite : sprites) {
		sprite->x = r.w/2;
		sprite->y = interval*i;
		i++;
	}
}

void MainMenuGameState::handle_event(SDL_Event e) {
	switch(e.type) {
	case SDL_MOUSEBUTTONDOWN:
		handle_mouse_down(e);
		break;
	}
}

void MainMenuGameState::handle_mouse_down(SDL_Event e) {
	int x = e.button.x;
	int y = e.button.y;
	int i = 0;
	Log::Infof("Handling click at (%d, %d)", x, y);
	for(Sprite *sprite : sprites) {
		if(sprite->contains(x,y)) {
			Log::Infof("Clicked button %d", i);
			this->button_pressed = i;
			break;
		}
		i++;
	}
}