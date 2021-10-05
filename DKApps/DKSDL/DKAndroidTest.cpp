#ifdef ANDROID
#include <SDL.h>
#ifdef USE_sdl2_ttf
	#include <SDL_ttf.h>
#endif

int DKAndroidTest();

//int main(int argc, char** argv) {
//	return DKAndroidTest();
//}

int DKAndroidTest(){
	SDL_Window *window;                   
	SDL_Init(SDL_INIT_VIDEO);      
#ifdef USE_sdl2_ttf	
	TTF_Init();
#endif
										   
	window = SDL_CreateWindow(
		"An SDL2 window",                  
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               
		480,                              
		SDL_WINDOW_OPENGL                  
	);

	if (window == NULL) {
		SDL_Log("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

#ifdef USE_sdl2_ttf
	TTF_Font* font = TTF_OpenFontRW(SDL_RWFromFile("fonts/OpenSans-Regular.ttf", "rb"), 1, 24);
	if (!font)
		SDL_Log("Could not load font %s\n", SDL_GetError());
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello World", textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect rect_tex = { 200, 200, surface ? surface->w : 0, surface ? surface->h : 0 };
	SDL_FreeSurface(surface);
#endif

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e))
			if (e.type == SDL_QUIT)
				break;

		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_Rect rect = {100, 100, 200, 200};
		SDL_RenderFillRect(renderer, &rect);
#ifdef USE_sdl2_ttf
		if (texture)
			SDL_RenderCopy(renderer, texture, NULL, &rect_tex);
#endif
		SDL_RenderPresent(renderer);
	}
#ifdef USE_sdl2_ttf
	if (texture)
		SDL_DestroyTexture(texture);
#endif
	if (renderer)
		SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
#ifdef USE_sdl2_ttf
	TTF_Quit();
#endif
	SDL_Quit();
	return 0;
}
#endif// ANDROID