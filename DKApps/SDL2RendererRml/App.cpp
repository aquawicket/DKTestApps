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

#include "App.h"
#include "Framerate.h"
#include <fstream>


bool App::active;
Rml::String App::file;
Rml::String App::mTitle;
SDL_Window* App::mWindow;
SDL_Renderer* App::mRenderer;
Rml::Context* App::mContext;
RmlUiSDL2Renderer* App::Renderer;
RmlUiSDL2SystemInterface App::mSystemInterface;
#ifdef IOS
int App::window_x = 0;
int App::window_y = 0;
int App::window_width = 320;
int App::window_height = 480;
#else
int App::window_x = SDL_WINDOWPOS_CENTERED;
int App::window_y = SDL_WINDOWPOS_CENTERED;
int App::window_width = 800;
int App::window_height = 600;
#endif

void App::init()
{
#ifdef RMLUI_PLATFORM_WIN32
	//AllocConsole();
#endif
    SDL_SetMainReady(); //Bypass SDLmain  //https://wiki.libsdl.org/SDL_SetMainReady
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("ERROR: SDL_Init( SDL_INIT_VIDEO ) failed: %s\n", SDL_GetError());

    //SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    int flags;
#ifdef IOS
    flags = SDL_WINDOW_OPENGL;
#else
    flags = SDL_WINDOW_RESIZABLE;
#endif
	SDL_Window* sdl_window = SDL_CreateWindow("RmlUi SDL2 with SDL_Renderer", window_x, window_y, window_width, window_height, flags);
	if (!sdl_window)
		printf("SDL_Window* invalid: %s\n", SDL_GetError());
	mWindow = sdl_window;

    SDL_Renderer* renderer = SDL_CreateRenderer(sdl_window, -1, 0);//SDL_RENDERER_ACCELERATED/* | SDL_RENDERER_PRESENTVSYNC*/);
	if (!renderer)
		printf("renderer invalid: %s\n", SDL_GetError());
	mRenderer = renderer;
    
	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(mRenderer, &info) < 0)
		printf("SDL_GetRendererInfo() failed: %s\n", SDL_GetError());

	// Print the SDL_Render name, and display it in the mTitle bar
	Rml::String renderer_name = info.name;
	printf("SDL_Renderer Driver = %s\n", renderer_name.c_str());
	mTitle = Rml::String("SDL_Renderer RmlUi - " + renderer_name);
	SDL_SetWindowTitle(sdl_window, mTitle.c_str());

	//RmlUiSDL2Renderer Renderer(mRenderer, mWindow);
	Renderer = new RmlUiSDL2Renderer(mRenderer, mWindow);

	FileInterfaceSDL2 FileInterface(FileInterfaceSDL2::FindSamplesRoot(App::file));
	Rml::SetFileInterface(&FileInterface);
	
	Rml::SetRenderInterface(Renderer);
	Rml::SetSystemInterface(&mSystemInterface);

	if (!Rml::Initialise())
		printf("Rml::Initialise() failed\n");

	struct FontFace 
	{
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
	if (App::file.empty())
	{
		App::file = "assets/demo.rml";
	}
	Rml::ElementDocument* Document = Context->LoadDocument(App::file); //Path to resources

	if (Document) {
		Document->Show();
		fprintf(stdout, "Document loaded\n");
	}
	else {
		fprintf(stdout, "Document is nullptr\n");
	}
	App::active = true;
//#ifndef IOS
	App::loop();
	App::exit();
//#endif
}


void App::loop()
{
	while (App::active)
	{
		Framerate::LimitFramerate(120);
		App::do_frame();
	}
}
	
void App::draw_background(SDL_Renderer* renderer, int w, int h)
{
	SDL_Color col[2] = { { 100, 100, 100, 255 }, { 150, 150, 150, 255 } };
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

void App::do_frame()
{
	SDL_Event event;

	SDL_RenderClear(mRenderer);

	//adjust the Context if the window is resized
	SDL_GetWindowSize(mWindow, &window_width, &window_height);
    if(!mContext){
        printf("ERROR: The context is invalid\n");
        return;
    }
	if (window_width != mContext->GetDimensions().x || window_height != mContext->GetDimensions().y)
	{
		mContext->SetDimensions(Rml::Vector2i(window_width, window_height));
	}
	
	draw_background(mRenderer, window_width, window_height);
	App::mContext->Render();
	SDL_RenderPresent(mRenderer);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			active = false;
			break;

		case SDL_MOUSEMOTION:
			mContext->ProcessMouseMove(event.motion.x, event.motion.y, mSystemInterface.GetKeyModifiers());
			break;
		case SDL_MOUSEBUTTONDOWN:
			mContext->ProcessMouseButtonDown(mSystemInterface.TranslateMouseButton(event.button.button), mSystemInterface.GetKeyModifiers());
			break;

		case SDL_MOUSEBUTTONUP:
			mContext->ProcessMouseButtonUp(mSystemInterface.TranslateMouseButton(event.button.button), mSystemInterface.GetKeyModifiers());
			break;

		case SDL_MOUSEWHEEL:
			mContext->ProcessMouseWheel(float(event.wheel.y), mSystemInterface.GetKeyModifiers());
			break;

		case SDL_KEYDOWN:
		{
			// Intercept F11 key stroke to toggle Fullscreen
			if (event.key.keysym.sym == SDLK_F11)
			{
				long FullscreenFlag = SDL_WINDOW_FULLSCREEN;
				bool isFullscreen = ((SDL_GetWindowFlags(mWindow) & FullscreenFlag) != 0);
				isFullscreen ? SDL_SetWindowFullscreen(mWindow, 0) : SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
				break;
			}
			// Intercept F12 key stroke to toggle RmlUi's visual debugger tool
			if (event.key.keysym.sym == SDLK_F12)
			{
				Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
				break;
			}

			mContext->ProcessKeyDown(mSystemInterface.TranslateKey(event.key.keysym.sym), mSystemInterface.GetKeyModifiers());
			break;
		}

		default:
			break;
		}
	}
	mContext->Update();

	// update framerate in the window Titlebar
	Rml::String post_mTitle = mTitle + " : " + std::to_string(Framerate::GetFps()) + "fps";
	SDL_SetWindowTitle(mWindow, post_mTitle.c_str());
}

void App::exit() 
{
	active = false;
	Rml::Shutdown();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}



int main(int argc, char** argv)
{
/*
#ifdef IOS
	@autoreleasepool{
		return UIApplicationMain(argc, argv, nil, @"iphoneViewerAppDelegate");
	}
#else
 */
	App app();
	if (argc > 1){
		App::file = argv[1];
	}
	App::init();
//#endif
	return 0;
}
