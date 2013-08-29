#pragma once
#include "ResourceManager.h"
#include <SDL_ttf.h>
#include <string>

class FontManager : public ResourceManager<TTF_Font>
{
protected:
	virtual TTF_Font *load_from_file(std::string filename);
	virtual void dispose(TTF_Font *resource);
public:
	FontManager(void);
	~FontManager(void);
	static FontManager &inst();
};