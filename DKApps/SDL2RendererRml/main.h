#ifndef MAIN_H
#define MAIN_H

#ifdef IOS
	#import <UIKit/UIKit.h>
#endif

#include <SDL.h>
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

class App
{
public:
	App(int argc, char** argv);
	static void init();
	static void loop();
	static void do_frame();
	static void exit();
	
	static SDL_Window* mScreen;
	static SDL_Renderer* mRenderer;
	static Rml::Context* mContext;
	static RmlUiSDL2SystemInterface SystemInterface;
	static int window_width;
	static int window_height;
	static bool active;
};

#ifdef IOS
@interface iphoneViewerAppDelegate : NSObject <UIApplicationDelegate, UIAccelerometerDelegate>{
	UIAccelerationValue        accel[3];
}

@property (nonatomic, retain) UIWindow *_window;
- (void)updateScene;
@end
#endif //ISO

#endif