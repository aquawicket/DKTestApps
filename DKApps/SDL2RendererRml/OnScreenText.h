/*
* This source file is part of digitalknob, the cross-platform C/C++/Javascript/Html/Css Solution
*
* For the latest information, see https://github.com/aquawicket/DigitalKnob
*
* Copyright(c) 2010 - 2022 Digitalknob Team, and contributors
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright noticeand this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

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
	static int Create(const std::string& label, const std::string text, const int x, const int y);
	static void SetText(const int& i, const std::string& text);
	static void Render(const int& i);
	static void Draw(const std::string& label, std::string text, const int x, const int y);
	static std::vector<OSText> mOsText;
	static SDL_Renderer* mSdlRenderer;
};

#endif