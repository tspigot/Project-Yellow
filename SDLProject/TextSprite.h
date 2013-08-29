#pragma once
#include "sprite.h"
#include <SDL_ttf.h>
#include <string>

class TextSprite :
	public Sprite
{
public:
	TextSprite(TTF_Font *f, std::string text, SDL_Color fg, SDL_Color bg, int x, int y, Anchor a=ANCHOR_TOPLEFT);
	virtual ~TextSprite(void);
};

