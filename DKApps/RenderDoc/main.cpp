#include <string.h>
#include <windows.h>
#include <SDL.h>
//#include <GL/glew.h>

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
	bool done = false;
	while (!done){
		SDL_Event event;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event)){
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
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	*/
	
	//System init
	if(!SDL_WasInit(SDL_INIT_EVERYTHING))
		SDL_Init(SDL_INIT_EVERYTHING);

	this->SDL_window = SDL_CreateWindow(title,10,10,w,h,SDL_WINDOW_OPENGL);
	if(this->SDL_window!=NULL){
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		this->context = SDL_GL_CreateContext(SDL_window);
		if(!this->context){
			SDL_DestroyWindow(SDL_window);
			COUT<<"FAILED TO CREATE CONTEXT. PRINTING ERROR AND THROWING EXCEPTION"<<ENDL;
			COUT<<SDL_GetError()<<ENDL;
			throw "ENGINE::WINDOW::GLCONTEXTERR";
		}
        glewExperimental = GL_TRUE;
        glewInit();
	}
	else{
		COUT<<"FAILED TO CREATE WINDOW. PRINTING ERROR AND THROWING EXCEPTION"<<ENDL;
		COUT<<SDL_GetError()<<ENDL;
		throw "ENGINE::WINDOW::SDLWINDOWERR";
	}
	return 0;
}
