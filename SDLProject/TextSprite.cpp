#include "TextSprite.h"
#include "FontManager.h"

TextSprite::TextSprite(TTF_Font *f, std::string text, SDL_Color fg, SDL_Color bg, int x, int y, Anchor a)
	: Sprite(TTF_RenderText_Shaded(f, text.c_str(), fg, bg), x, y, a)
{
}


TextSprite::~TextSprite(void)
{
	SDL_FreeSurface(this->surf);
}
