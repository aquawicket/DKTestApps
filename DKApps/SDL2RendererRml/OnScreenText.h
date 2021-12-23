#ifndef ONSCREENTEXT_H
#define ONSCREENTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>

class OnScreenText
{
	OnScreenText(SDL_Window* sdlWindow);
	bool SetText(const std::string& text);
	
	SDL_Window* mSdlWindow;
	TTF_Font* mFont;
	SDL_Texture* mSdlTexture;
	SDL_Surface* mSdlSurface;
	SDL_Color mColor;
};

#endif