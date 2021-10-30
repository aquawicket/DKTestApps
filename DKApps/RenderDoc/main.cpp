#include <string.h>
#include <windows.h>
#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

int main(int /*argc*/, char** /*argv*/){
	/*
	AllocConsole();
	int window_width = 1024;
	int window_height = 768;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* screen = SDL_CreateWindow("LibRmlUi SDL2 test", 20, 20, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);
	int oglIdx = -1;
	int nRD = SDL_GetNumRenderDrivers();
	for (int i = 0; i < nRD; i++){
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info)){
			if (!strcmp(info.name, "opengl")){
				oglIdx = i;
			}
		}
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//GLenum err = glewInit();
	//if (err != GLEW_OK)
	//	fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	//glLoadIdentity();
	//glOrtho(0, window_width, window_height, 0, 0, 1);
	*/
	
	//System init
	if(!SDL_WasInit(SDL_INIT_EVERYTHING))
		SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* sdl_window = SDL_CreateWindow("RenderDocTeast", 10, 10, 800, 600, SDL_WINDOW_OPENGL);
	if(sdl_window!=NULL){
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GLContext context = SDL_GL_CreateContext(sdl_window);
		if(!context){
			SDL_DestroyWindow(sdl_window);
			printf("FAILED TO CREATE CONTEXT. PRINTING ERROR AND THROWING EXCEPTION");
			printf("%s", SDL_GetError());
		}
        glewExperimental = GL_TRUE;
        glewInit();
	}
	else{
		printf("FAILED TO CREATE WINDOW.PRINTING ERROR AND THROWING EXCEPTION");
		printf("%s", SDL_GetError());
	}

	bool done = false;
	while (!done) {
		/*
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		*/
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			default:
				break;
			}
		}
	}
	/*
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(screen);
	*/
	SDL_Quit();
	return 0;
}
