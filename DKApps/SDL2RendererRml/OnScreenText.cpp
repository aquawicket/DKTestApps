#include "OnScreenText.h"
#include <FileInterface.h>

std::vector<OSText> OnScreenText::mOsText;
SDL_Renderer* OnScreenText::mSdlRenderer;
SDL_Surface* OnScreenText::mSdlSurface;

bool OnScreenText::Init(SDL_Renderer* sdlRenderer)
{
	mSdlRenderer = sdlRenderer;
	TTF_Init();
	return true;
}

OSText* OnScreenText::Create(const std::string& label, const std::string text, const int& x, const int& y)//, const std::string& font, const int& size, const SDL_Color& color)
{
	OSText osText;
	osText.label = label;
	osText.text = text;
	std::string font_file = "assets/LatoLatin-Regular.ttf"; //DEFAULT
	std::string font_path = FileInterface::mRoot + font_file;
	osText.size = 20; //DEFAULT
	osText.font = TTF_OpenFont(font_path.c_str(), osText.size);
	if (!osText.font) {
		printf("Error: could not load font %s\n", font_file.c_str());
		return nullptr;
	}
	osText.color = { 0,0,0 }; //DEFAULT
	osText.rect.x = x;
	osText.rect.y = y;

	SDL_Surface* sdlSurface = TTF_RenderText_Solid(osText.font, osText.text.c_str(), osText.color);
	osText.mSdlTexture = SDL_CreateTextureFromSurface(mSdlRenderer, sdlSurface);
	if (!osText.mSdlTexture) {
		printf("The Texture is Invalid\n");
		return nullptr;
	}
	SDL_QueryTexture(osText.mSdlTexture, NULL, NULL, &osText.rect.w, &osText.rect.h);
	mOsText.push_back(osText);
	SDL_FreeSurface(mSdlSurface);
	return &mOsText[mOsText.size() - 1];
}

bool OnScreenText::SetText(const std::string& label, const std::string& text)
{
	for (unsigned int i = 0; i < mOsText.size(); ++i) {
		if (mOsText[i].label == label) {
			if (mOsText[i].text != text) {
				mOsText[i].text = text;
				SDL_Surface* sdlSurface = TTF_RenderText_Solid(mOsText[i].font, mOsText[i].text.c_str(), mOsText[i].color);
				mOsText[i].mSdlTexture = SDL_CreateTextureFromSurface(mSdlRenderer, mSdlSurface);
				SDL_FreeSurface(sdlSurface);
				return true;
			}
		}
	}
	printf("Error: SetText could not find the element\n");
	return false;
}

void OnScreenText::Render(const OSText& osText)
{
	SDL_RenderCopy(mSdlRenderer, osText.mSdlTexture, NULL, &osText.rect);
}

//Single funtion to create and draw within a render loop 
void OnScreenText::Draw(const std::string& label, const std::string& text, const int& x, const int& y)
{
	for (unsigned int i = 0; i < mOsText.size(); ++i) {
		if (mOsText[i].label == label) {
			if (mOsText[i].text != text) {
				SetText(label, text);
			}
			Render(mOsText[i]);
			return;
		}
	}
	
	OSText* mOsText = Create(label, text, x, y);
	if (mOsText)
		Render(*mOsText);	
}