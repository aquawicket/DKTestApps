#if defined(WIN32) || defined(MAC)
#include <GL/glew.h>
#endif
#ifdef RMLUI_PLATFORM_WIN32
#include <windows.h>
#endif
#include <string.h>
#include <iostream>
#include <filesystem>
#include <SDL.h>
#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/StringUtilities.h>
#include <RmlUi/Debugger/Debugger.h>

#include "RmlApp.h"
#include "RmlMain.h"
#include "RmlFile.h"
#include "RmlUtility.h"
 //#include <Shell.h>
 //#include <ShellFileInterface.h>
#include "SDLRmlSystem.h"
#include "SDLRmlRenderer.h"

bool RmlApp::paused = false;

int main(int /*argc*/, char** /*argv*/)
{
#ifdef RMLUI_PLATFORM_WIN32
	//AllocConsole();
#endif

	int window_width = 1024;
	int window_height = 768;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow("LibRmlUi SDL2 test", 20, 20, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);
	int oglIdx = -1;
	int nRD = SDL_GetNumRenderDrivers();
	for (int i = 0; i < nRD; i++){
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info)){
			if (!strcmp(info.name, "opengl"))
				oglIdx = i;
		}
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	GLenum err = glewInit();

	if (err != GLEW_OK){
		fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
		//RMLERROR("ERROR"+ std::to_string(glewGetErrorString(err))+"\n")
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, window_width, window_height, 0, 0, 1);

	//EDIT: digitalknob
	//print opengl info
	printf("OpenGL Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL Version:  %s\n", glGetString(GL_VERSION));
	//print sdl results
	int profile;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
	printf("SDL_GL_CONTEXT_PROFILE_MASK = %d\n", profile);
	int major;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	printf("SDL_GL_CONTEXT_MAJOR_VERSION = %d\n", major);
	int minor;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	printf("SDL_GL_CONTEXT_MINOR_VERSION = %d\n", minor);

	SDLRmlRenderer rmlSdlRenderer(renderer, screen);
	SDLRmlSystem systemInterface;

	Rml::String assets{ std::filesystem::current_path().u8string() };
	RmlFile fileInterface(assets);

	Rml::SetFileInterface(&fileInterface);
	Rml::SetRenderInterface(&rmlSdlRenderer);
	Rml::SetSystemInterface(&systemInterface);

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
		Rml::LoadFontFace(face.filename, face.fallback_face);

	Rml::Context* Context = Rml::CreateContext("default",
		Rml::Vector2i(window_width, window_height));

	Rml::Debugger::Initialise(Context);
	Rml::ElementDocument* Document = Context->LoadDocument("SDLRml.rml"); //EDIT: digitalknob

	if (Document){
		Document->Show();
		fprintf(stdout, "\nDocument loaded");
	}
	else{
		fprintf(stdout, "\nDocument is nullptr");
	}

	bool done = false;
	while (!done){
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);

		Context->Render();
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)){
			switch (event.type){
			case SDL_QUIT:
				done = true;
				break;
			case SDL_MOUSEMOTION:
				Context->ProcessMouseMove(event.motion.x, event.motion.y, systemInterface.GetKeyModifiers());
				break;
			case SDL_MOUSEBUTTONDOWN:
				Context->ProcessMouseButtonDown(systemInterface.TranslateMouseButton(event.button.button), systemInterface.GetKeyModifiers());
				break;
			case SDL_MOUSEBUTTONUP:
				Context->ProcessMouseButtonUp(systemInterface.TranslateMouseButton(event.button.button), systemInterface.GetKeyModifiers());
				break;
			case SDL_MOUSEWHEEL:
				Context->ProcessMouseWheel(float(event.wheel.y), systemInterface.GetKeyModifiers());
				break;
			case SDL_KEYDOWN:
				// Intercept F8 key stroke to toggle RmlUi's visual debugger tool
				if (event.key.keysym.sym == SDLK_F8){
					Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
					break;
				}
				Context->ProcessKeyDown(systemInterface.TranslateKey(event.key.keysym.sym), systemInterface.GetKeyModifiers());
				break;
			default:
				break;
			}
		}
		Context->Update();
	}

	Rml::Shutdown();
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return 0;
}
