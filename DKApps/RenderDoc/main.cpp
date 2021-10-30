//Note: SDL_CreateRenderer sets the OpenGL version to 2.1
//You have to set the attributes after creating the render and before creating the context
//https://github.com/ocornut/imgui/issues/1116#issuecomment-297701113

#include <string.h>
#include <windows.h>
#include <SDL.h>
#include <GL/glew.h>
#include <stdio.h>

void checkSDLError(int line = -1) {
	const char* error = SDL_GetError();
	if (*error != '\0') {
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
}

int main(int /*argc*/, char** /*argv*/){
	AllocConsole();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error while initializing the SDL : % s\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	int width = 800;
	int height = 800;
	SDL_Window* window = SDL_CreateWindow("RenderDocTeast", 20, 20, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		printf("FAILED TO CREATE WINDOW\n");
		printf("%s\n", SDL_GetError());
		return false;
	}
	checkSDLError(__LINE__);

	int oglIdx = -1;
	int nRD = SDL_GetNumRenderDrivers();
	for (int i = 0; i < nRD; i++) {
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info)) {
			if (!strcmp(info.name, "opengl"))
				oglIdx = i;
		}
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	checkSDLError(__LINE__);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);

	/*
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));
		return false;
	}
	*/

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

	bool done = false;
	while (!done) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
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
	SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
