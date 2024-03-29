#pragma once
#ifndef SDLRml_H
#define SDLRml_H

#include <RmlUi/Core.h>
#include "SDLWindow.h"
#include "RmlMain.h"
#include "SDLRmlSystem.h"
#include "SDLRmlRenderer.h"


class SDLRml
{
public:
	SDLRml();
	bool Init();
	bool End();
	bool Handle(SDL_Event *event);
	void Render();
	void Update();
	//void ProcessEvent(Rml::Core::Event& event);
	
	SDLWindow* sdlWindow;
	RmlMain* rmlMain;
#ifdef RML_SHELL_RENDER
	ShellRenderInterfaceOpenGL* renderer;
#else
	SDLRmlRenderer* renderer;
#endif
	SDLRmlSystem* systemInterface;
};


#endif //SDLRml_H