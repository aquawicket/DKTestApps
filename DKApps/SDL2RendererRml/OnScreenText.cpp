#include "OnScreenText.h"
#include <FileInterface.h>

OnScreenText::OnScreenText(SDL_Renderer* sdlRenderer)
{
	mSdlRenderer = sdlRenderer;
	TTF_Init();
	std::string file = FileInterface::mRoot+"assets/NotoEmoji-Regular.ttf";
	mFont = TTF_OpenFont(file.c_str(), 20);
	if (!mFont) {
		printf("Error: could not load font %s\n", file.c_str());
		return;
	}
    mColor.r = 100;
    mColor.g = 100;
    mColor.b = 255;
	SetText(std::string("Test String"));
}

OnScreenText::~OnScreenText()
{
	//TODO: cleanup
}

bool OnScreenText::SetText(const std::string& text)
{
	mSdlSurface = TTF_RenderText_Solid(mFont, text.c_str(), mColor);
	mSdlTexture = SDL_CreateTextureFromSurface(mSdlRenderer, mSdlSurface);
	SDL_FreeSurface(mSdlSurface);
	return true;
}

void OnScreenText::Render()
{
	//DEBUG CODE
	/*
	SetText(" ");
	int dtexW = 0;
	int dtexH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &dtexW, &dtexH);
	int dleft = 0;
	int dtop = 0;
	SDL_Rect ddstrect = {dleft, dtop, dtexW, dtexH};
	SDL_RenderCopy(dkSdlWindow->renderer, texture, NULL, &ddstrect);
	SDL_DestroyTexture(texture);
	//return; //remove to turn fps counter on
	*/
	
	//Draw fps
	//unsigned int fps;
	//DKUtil::GetFps(fps);
	//DKString fpsString = toString(fps)+"fps";
	//SetText(fpsString);
	int x = 10;
	int y = 10;
	int w;
	int h;
	SDL_QueryTexture(mSdlTexture, NULL, NULL, &w, &h);
	SDL_Rect outRect = {x, y, w, h};
	SDL_RenderCopy(mSdlRenderer, mSdlTexture, NULL, &outRect);
	//SDL_DestroyTexture(mSdlTexture);
}
