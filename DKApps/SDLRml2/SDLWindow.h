#pragma once
#ifndef SDLWindow_H
#define SDLWindow_H

#include "SDL.h"
#include <map>

class SDLWindow
{
public:
	bool Init();
	bool End();
	static SDLWindow* Get();
	bool TestInt(const void* input, void* output);
	bool TestString(const void* input, void* output);
	bool TestReturnInt(const void* input, void* output);
	bool TestReturnString(const void* input, void* output);

	bool Fullscreen(const void* input, void* output);
	bool GetClipboard(const void* input, void* output);
	bool GetHandle(const void* input, void* output);
	bool GetHeight(const void* input, void* output);
	bool GetMouseX(const void* input, void* output);
	bool GetMouseY(const void* input, void* output);
	bool GetPixelRatio(const void* input, void* output);
	bool GetWidth(const void* input, void* output);
	bool GetX(const void* input, void* output);
	bool GetY(const void* input, void* output);
	bool Hide(const void* input, void* output);
	bool IsFullscreen(const void* input, void* output);
	bool IsVisible(const void* input, void* output);
	bool MessageBox(const void* input, void* output);
	bool Minimize(const void* input, void* output);
	bool Restore(const void* input, void* output);
	bool SetClipboard(const void* input, void* output);
	bool SetHeight(const void* input, void* output);
	bool SetIcon(const void* input, void* output);
	bool SetTitle(const void* input, void* output);
	bool SetWidth(const void* input, void* output);
	bool SetX(const void* input, void* output);
	bool SetY(const void* input, void* output);
	bool Show(const void* input, void* output);
	bool Windowed(const void* input, void* output);
	
	static int EventFilter(void* userdata, SDL_Event* event);
	static bool drawBackground(SDL_Renderer *renderer, int w, int h);
	bool handle(SDL_Event* event);
	void Process();
	static std::map<int,int> sdlKeyCode;
	static std::map<int,int> sdlCharCode;
	static std::map<int,int> sdlShiftCharCode;
	static std::map<int,int> sdlMacCode;
	void MapInputs();

	SDL_Window* window;
	SDL_Renderer* renderer;
	//SDL_GLContext context;
	std::string gl_major_version;
	std::string gl_minor_version;
	std::string gl_version;
	std::string gl_vendor;
	std::string gl_renderer;
	//std::string gl_shading;
	std::string gl_extensions;

	std::string mTitle;
	int winX;
	int winY;
	unsigned int width;
	unsigned int height;
	int last_mouseX;
	int last_mouseY;

	static std::vector<std::function<bool(SDL_Event* event)> > event_funcs;
	static std::vector<std::function<void()> > render_funcs;
	static std::vector<std::function<void()> > update_funcs;

	template<class T>
	static void AddEventFunc(bool (T::*func)(SDL_Event *event), T* _this){
		event_funcs.push_back(std::bind(func, _this, std::placeholders::_1));
	}

	template<class T>
	static void AddRenderFunc(void (T::*func)(), T* _this){
		render_funcs.push_back(std::bind(func, _this));
	}

	template<class T>
	static void AddRenderFuncFirst(void (T::*func)(), T* _this){
		render_funcs.insert(render_funcs.begin(), std::bind(func, _this));
	}

	template<class T>
	static void AddUpdateFunc(void (T::* func)(), T* _this){
		update_funcs.push_back(std::bind(func, _this));
	}
};

#endif //SDLWindow_H
