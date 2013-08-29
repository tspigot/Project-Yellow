#pragma once
#include <string>
#include <SDL.h>

#include "ResourceManager.h"

class ImageManager : public ResourceManager<SDL_Surface> {
protected:
	virtual SDL_Surface *load_from_file(std::string filename) override;
	virtual void dispose(SDL_Surface *s) override;
public:
	ImageManager();
	~ImageManager();
	static ImageManager &inst();
};