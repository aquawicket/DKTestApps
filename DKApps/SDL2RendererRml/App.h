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

#ifndef APP_H
#define APP_H

#ifdef RMLUI_PLATFORM_WIN32
#include <windows.h>
#endif

#ifdef IOS
	#import <UIKit/UIKit.h>
#endif

#include <SDL.h>
#include <RmlUi/Core.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Debugger/Debugger.h>

#include "FileInterfaceSDL2.h"
#include "SystemInterfaceSDL2.h"
#include "RenderInterfaceSDL2.h"

#include <string.h>

class App
{
public:
	App(int argc, char** argv) {};
	static void init();
	static void loop();
	static void draw_background(SDL_Renderer* renderer, int w, int h);
	static void do_frame();
	static void exit();
	
	static Rml::String mTitle;
	static SDL_Window* mWindow;
	static SDL_Renderer* mRenderer;
	static Rml::Context* mContext;
	static RmlUiSDL2SystemInterface mSystemInterface;
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