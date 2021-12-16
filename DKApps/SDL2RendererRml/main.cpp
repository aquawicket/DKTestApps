/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 Nuno Silva
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Debugger/Debugger.h>
#include <string.h>

#include "FileInterfaceSDL2.h"
#include "SystemInterfaceSDL2.h"
#include "RenderInterfaceSDL2.h"

#ifdef RMLUI_PLATFORM_WIN32
#include <windows.h>
#endif

#include <SDL.h>

bool ERR(std::string message, std::string lastError = "") {
	std::string full_message = "ERROR: "+ message + "\n" + lastError + "\n";
	printf("%s ", full_message.c_str());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", full_message.c_str(), NULL);
	throw;
	exit;
	return false;
}

bool WARN(std::string message, std::string lastError = "") {
	std::string full_message = "Warning: " + message + "\n" + lastError + "\n";
	printf("%s ", full_message.c_str());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", full_message.c_str(), NULL);
	return true;
}

static void draw_background(SDL_Renderer* renderer, int w, int h)
{
	SDL_Color col[2] = {{ 100, 100, 100, 255 }, { 150, 150, 150, 255 }};
	SDL_Rect rect({ 0,0,8,8 });
	int i, x, y;
	for (y = 0; y < h; y += rect.h) {
		for (x = 0; x < w; x += rect.w) {
			i = (((x ^ y) >> 3) & 1);
			rect.x = x;
			rect.y = y;
			SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

int main(int argc, char** argv)
{
#ifdef RMLUI_PLATFORM_WIN32
	AllocConsole();
#endif

    int window_width = 800;
    int window_height = 600;

    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
		ERR("ERROR: SDL_Init( SDL_INIT_VIDEO ) failed", SDL_GetError());

	SDL_Window* screen = SDL_CreateWindow("RmlUi SDL2 with SDL_Renderer test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE);
	if (!screen)
		ERR("SDL_Window* invalid", SDL_GetError());

	int w, h;
	SDL_GetWindowSize(screen, &w, &h);

	int top, left, bottom, right;
	SDL_GetWindowBordersSize(screen, &top, &left, &bottom, &right);

	SDL_Renderer * renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		ERR("renderer invalid", SDL_GetError());

	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(renderer, &info) < 0)
		ERR("SDL_GetRendererInfo() failed", SDL_GetError());

	printf("Render Driver = %s\n", std::string(info.name).c_str());

	RmlUiSDL2Renderer Renderer(renderer, screen);
	RmlUiSDL2SystemInterface SystemInterface;

	Rml::String root = ShellFileInterface::FindSamplesRoot();
	ShellFileInterface FileInterface(root);

	Rml::SetFileInterface(&FileInterface);
	Rml::SetRenderInterface(&Renderer);
	Rml::SetSystemInterface(&SystemInterface);

	if (!Rml::Initialise())
		return 1;

	struct FontFace {
		Rml::String filename;
		bool fallback_face;
	};
	FontFace font_faces[] = {
		{ "LatoLatin-Regular.ttf",    false },
		{ "LatoLatin-Italic.ttf",     false },
		{ "LatoLatin-Bold.ttf",       false },
		{ "LatoLatin-BoldItalic.ttf", false },
		{ "NotoEmoji-Regular.ttf",    true  },
	};

	for (const FontFace& face : font_faces)
	{
		Rml::LoadFontFace("assets/" + face.filename, face.fallback_face);
	}

	Rml::Context* Context = Rml::CreateContext("default",
		Rml::Vector2i(window_width, window_height));

	Rml::Debugger::Initialise(Context);

	Rml::ElementDocument* Document = Context->LoadDocument("assets/demo.rml");

	if (Document)
	{
		Document->Show();
		fprintf(stdout, "Document loaded\n");
	}
	else
	{
		fprintf(stdout, "Document is nullptr\n");
	}

	bool done = false;

	while (!done)
	{
		SDL_Event event;
		SDL_RenderClear(renderer);
		draw_background(renderer, window_width, window_height);
		Context->Render();
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;

			case SDL_MOUSEMOTION:
				Context->ProcessMouseMove(event.motion.x, event.motion.y, SystemInterface.GetKeyModifiers());
				break;
			case SDL_MOUSEBUTTONDOWN:
				Context->ProcessMouseButtonDown(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
				break;

			case SDL_MOUSEBUTTONUP:
				Context->ProcessMouseButtonUp(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
				break;

			case SDL_MOUSEWHEEL:
				Context->ProcessMouseWheel(float(event.wheel.y), SystemInterface.GetKeyModifiers());
				break;

			case SDL_KEYDOWN:
			{
				// Intercept F8 key stroke to toggle RmlUi's visual debugger tool
				if (event.key.keysym.sym == SDLK_F8)
				{
					Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
					break;
				}

				Context->ProcessKeyDown(SystemInterface.TranslateKey(event.key.keysym.sym), SystemInterface.GetKeyModifiers());
				break;
			}

			default:
				break;
			}
		}
		Context->Update();
	}

	Rml::Shutdown();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

	return 0;
}



// For iphone, iPad
#ifdef IOS
int retval = UIApplicationMain(argc, argv, nil, @"iphoneViewerAppDelegate");
#endif