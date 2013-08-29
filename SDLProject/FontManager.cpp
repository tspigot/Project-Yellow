#include "FontManager.h"
#include <regex>
#include "Log.h"
#include <SDL_ttf.h>

FontManager::FontManager() :
	ResourceManager<TTF_Font>()
{
}


FontManager::~FontManager(void)
{
}

TTF_Font *FontManager::load_from_file(std::string filename) {
	std::smatch sm;
	Log::Infof("Filename: %s", filename.c_str());
	std::regex_match(filename, sm, std::regex("(.*\\.ttf) (\\d+)"));
	if(sm.size() != 3) {
		Log::Errorf("Invalid font string: %s", filename.c_str());
		return NULL;
	}
	return TTF_OpenFont(std::string(sm[1]).c_str(), std::stoi(std::string(sm[2])));
}

void FontManager::dispose(TTF_Font *f) {
	TTF_CloseFont(f);
}

FontManager &FontManager::inst() {
	static FontManager inst;
	return inst;
}