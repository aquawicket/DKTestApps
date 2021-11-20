#pragma once
#ifndef SDLRml_H
#define SDLRml_H

#include <RmlUi/Core.h>
#include "SDLWindow.h"
#include "RmlMain.h"
#include "SDLRmlSystem.h"
#include "SDLRmlRenderer.h"


class SDLRml// : public ObjectT<SDLRml>
{
public:
	bool Init();
	bool End();

	bool Handle(SDL_Event *event);
	void Render();
	void Update();
	//void ProcessEvent(Rml::Core::Event& event);
	
	SDLWindow* sdlWindow;
	RmlMain* rmlmain;
#ifdef RML_SHELL_RENDER
	ShellRenderInterfaceOpenGL* Renderer;
#else
	SDLRmlRenderer* renderer;
#endif
	SDLRmlSystem* systemInterface;
};


#endif //SDLRml_H