#ifndef ONSCREENTEXT_H
#define ONSCREENTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class OnScreenText
{
public:
	OnScreenText(SDL_Renderer* sdlRenderer);
	~OnScreenText();
	bool SetText(const std::string& text);
	void Render();

	SDL_Renderer* mSdlRenderer;
	SDL_Surface* mSdlSurface;
	SDL_Texture* mSdlTexture;	
	SDL_Color mColor;
	TTF_Font* mFont;
};

#endif