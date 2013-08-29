#include "ImageManager.h"
#include "Log.h"

#include <SDL.h>
#include <SDL_image.h>

ImageManager::ImageManager() {
}

ImageManager::~ImageManager() {
}

void ImageManager::dispose(SDL_Surface *s) {
	SDL_FreeSurface(s);
}

SDL_Surface *ImageManager::load_from_file(std::string name) {
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	loaded_image = IMG_Load(name.c_str());
	if(loaded_image != NULL) {
		optimized_image = SDL_DisplayFormatAlpha(loaded_image);
		SDL_FreeSurface(loaded_image); 
		if(optimized_image == NULL) {
			Log::Errorf("Error optimizing image %s: %s", name.c_str(), IMG_GetError());
		}
	} else { 
		Log::Errorf("Error loading image %s: %s", name.c_str(), IMG_GetError());
	}
	return optimized_image;
}

ImageManager &ImageManager::inst() {
	static ImageManager inst;
	return inst;
}