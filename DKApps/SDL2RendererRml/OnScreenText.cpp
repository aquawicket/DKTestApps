#include "OnScreenText.h"
#include <FileInterface.h>

OnScreenText::OnScreenText(SDL_Window* sdlWindow)
{
	TTF_Init();
	std::string file = FileInterface::root+"arial.ttf";
	font = TTF_OpenFont(file.c_str(), 20);
    color.r = 100;
    color.g = 100;
    color.b = 255;
	SetText(std::string("Test String"));
}

bool OnScreenText::SetText(const std::string& text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	mSdlTexture = SDL_CreateTextureFromSurface(mSdlWindow->renderer, mSdlSurface);
	SDL_FreeSurface(mSdlSurface);
	return true;
}

void DKSDLText::Render()
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
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(mSdlTexture, NULL, NULL, &texW, &texH);
	int left = 5;
	int top = mSdlWindow->height - texH;
	SDL_Rect outRect = {left, top, texW, texH};
	SDL_RenderCopy(mSdlWindow->renderer, mSdlTexture, NULL, &outRect);
	//SDL_DestroyTexture(mSdlTexture);
}