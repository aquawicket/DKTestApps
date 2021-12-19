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

#include "main.h"

SDL_Window* App::mScreen;
SDL_Renderer* App::mRenderer;
Rml::Context* App::mContext;
RmlUiSDL2SystemInterface App::SystemInterface;
#ifdef IOS
    int App::window_width = 320;
    int App::window_height = 480;
#else
    int App::window_width = 800;
    int App::window_height = 600;
#endif
bool App::active;
	
	
bool ERR(std::string message, std::string lastError = "") {
	std::string full_message = "ERROR: "+ message + "\n" + lastError + "\n";
	printf("%s ", full_message.c_str());
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", full_message.c_str(), NULL);
	//throw;
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
#ifdef IOS
	@autoreleasepool{
		return UIApplicationMain(argc, argv, nil, @"iphoneViewerAppDelegate");
	}
#else
	App app(argc, argv);
	App::init();
#endif
	return 0;
}

App::App(int argc, char** argv)
{

}


void App::init()
{
#ifdef RMLUI_PLATFORM_WIN32
	AllocConsole();
#endif
    SDL_SetMainReady(); //Bypass SDLmain  //https://wiki.libsdl.org/SDL_SetMainReady
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ERR("ERROR: SDL_Init( SDL_INIT_VIDEO ) failed", SDL_GetError());

    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
#if defined(ANDROID) || defined(IOS)
    printf("Creating SDLWindow for mobile device\n");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_Window* screen;
    SDL_Renderer* renderer;
    if(SDL_CreateWindowAndRenderer(window_width, window_height, SDL_WINDOW_RESIZABLE, &screen, &renderer) < 0)
        ERR("SDL_Window* invalid", SDL_GetError());
#else
	SDL_Window* screen = SDL_CreateWindow("RmlUi SDL2 with SDL_Renderer test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE);
	if (!screen)
		ERR("SDL_Window* invalid", SDL_GetError());
	mScreen = screen;

	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		ERR("renderer invalid", SDL_GetError());
	mRenderer = renderer;
#endif
    
	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(mRenderer, &info) < 0)
		ERR("SDL_GetRendererInfo() failed", SDL_GetError());

	printf("Render Driver = %s\n", std::string(info.name).c_str());

	RmlUiSDL2Renderer Renderer(mRenderer, mScreen);

	Rml::String root = ShellFileInterface::FindSamplesRoot();
	ShellFileInterface FileInterface(root);

	Rml::SetFileInterface(&FileInterface);
	Rml::SetRenderInterface(&Renderer);
	Rml::SetSystemInterface(&SystemInterface);

	if (!Rml::Initialise())
		ERR("Rml::Initialise() failed");

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

	for (const FontFace& face : font_faces) {
		Rml::LoadFontFace("assets/" + face.filename, face.fallback_face);
	}

	Rml::Context* Context = Rml::CreateContext("default",
		Rml::Vector2i(window_width, window_height));
	mContext = Context;

	Rml::Debugger::Initialise(Context);
	Rml::ElementDocument* Document = Context->LoadDocument("assets/demo.rml");

	if (Document) {
		Document->Show();
		fprintf(stdout, "Document loaded\n");
	}
	else {
		fprintf(stdout, "Document is nullptr\n");
	}
	App::active = true;
	App::loop();
	App::exit();
}


void App::loop()
{
	while (App::active)
	{
		//limit_framerate();
		App::do_frame();
	}
}
	
	
void App::do_frame()
{
	SDL_Event event;
	SDL_RenderClear(mRenderer);
	draw_background(mRenderer, window_width, window_height);
	mContext->Render();
	SDL_RenderPresent(mRenderer);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			active = false;
			break;

		case SDL_MOUSEMOTION:
			mContext->ProcessMouseMove(event.motion.x, event.motion.y, SystemInterface.GetKeyModifiers());
			break;
		case SDL_MOUSEBUTTONDOWN:
			mContext->ProcessMouseButtonDown(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
			break;

		case SDL_MOUSEBUTTONUP:
			mContext->ProcessMouseButtonUp(SystemInterface.TranslateMouseButton(event.button.button), SystemInterface.GetKeyModifiers());
			break;

		case SDL_MOUSEWHEEL:
			mContext->ProcessMouseWheel(float(event.wheel.y), SystemInterface.GetKeyModifiers());
			break;

		case SDL_KEYDOWN:
		{
			// Intercept F8 key stroke to toggle RmlUi's visual debugger tool
			if (event.key.keysym.sym == SDLK_F8)
			{
				Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
				break;
			}

			mContext->ProcessKeyDown(SystemInterface.TranslateKey(event.key.keysym.sym), SystemInterface.GetKeyModifiers());
			break;
		}

		default:
			break;
		}
	}
	mContext->Update();
}

void App::exit() 
{
	active = false;
	Rml::Shutdown();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mScreen);
    SDL_Quit();
}

