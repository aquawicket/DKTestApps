#pragma once
#ifndef SDLRml_H
#define SDLRml_H

#include <RmlUi/Core.h>
#include "SDLWindow/SDLWindow.h"
#include "Rml/Rml.h"
#include "SDLRml/SDLRmlSystem.h"
#include "SDLRml/SDLRmlRenderer.h"


class SDLRml : public ObjectT<SDLRml>
{
public:
	bool Init();
	bool End();

	bool Handle(SDL_Event *event);
	void Render();
	void Update();
	//void ProcessEvent(Rml::Core::Event& event);
	
	SDLWindow* sdlWindow;
	Rml* rml;
#ifdef RML_SHELL_RENDER
	ShellRenderInterfaceOpenGL* Renderer;
#else
	SDLRmlRenderer* Renderer;
#endif
	SDLRmlSystem* SystemInterface;
};


REGISTER_OBJECT(SDLRml, true)
#endif //SDLRml_H