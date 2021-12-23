#ifndef ONSCREENTEXT_H
#define ONSCREENTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

struct OSText {
	std::string label;
	std::string text;
	TTF_Font* font;
	int size;
	SDL_Color color;
	SDL_Rect rect;
	SDL_Texture* mSdlTexture;
};

class OnScreenText
{
public:
	static bool Init(SDL_Renderer* sdlRenderer);
	static OSText* Create(const std::string& label, const std::string text, const int& x, const int& y);// , const std::string& font, const int& size, const SDL_Color& color);
	static bool SetText(const std::string& label, const std::string& text);
	static void Render(const OSText& osText);
	static SDL_Renderer* mSdlRenderer;
	static SDL_Surface* mSdlSurface;
	static void Draw(const std::string& label, const std::string& text, const int& x = -1, const int& y = -1);
	static std::vector<OSText> mOsText;
};

#endif