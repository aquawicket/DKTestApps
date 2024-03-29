#if !IOS && !ANDROID
	#define SDL_MAIN_HANDLED
#else
	#include "SDL_main.h"
#endif
#include "App.h"

int main(int argc, char** argv)
{
#if !IOS
	SDL_SetMainReady();
#endif
	if (argc > 1)
		App::mFile = argv[1];

	App app;
	app.init();
	return 0;
}
