//#include "DK/stdafx.h"
#include "SDL.h"
//#include "DK/DKFile.h"
//#include "DKAssets/DKAssets.h"
#include "SDLRml/SDLRml.h"

bool SDLRml::Init(){
	//Android SDL_TEXTINPUT events not working
	//SDL_StartTextInput(); 
	//SDL_EventState(SDL_TEXTINPUT, SDL_ENABLE);
	
	SdlWindow = DKSDLWindow::Instance("DKSDLWindow0");
	Rml = Rml::Instance("Rml0");
	if(!SdlWindow || !Rml)
		return ERROR("SDLRml::Init(): INVALID OBJECTS\n");
#ifdef RML_SHELL_RENDER
	Renderer = new ShellRenderInterfaceOpenGL();
#else
	Renderer = new RmlSDL2Renderer(SdlWindow->renderer, SdlWindow->window);
#endif
	SystemInterface = new RmlSDL2SystemInterface();
	Rml::SetRenderInterface(Renderer);
    Rml::SetSystemInterface(SystemInterface);
	SDLWindow::AddEventFunc(&SDLRml::Handle, this);
	SDLWindow::AddRenderFunc(&SDLRml::Render, this);
	SDLWindow::AddUpdateFunc(&SDLRml::Update, this);
	return true;
}

bool SDLRml::End(){
	return true;
}

bool DKSDLRml::Handle(SDL_Event *event) {
	if(!Rml->document)
		return ERROR("Rml->document invalid");
	Rml::Element* hover;
	switch(event->type){
		case SDL_MOUSEMOTION:
			Rml->context->ProcessMouseMove(event->motion.x, event->motion.y, SystemInterface->GetKeyModifiers());
			//if we clicked an element, end the event.
			hover = Rml->context->GetHoverElement();
			if(hover && (!has(hover->GetId(), "iframe_")))
				return true;
            break;   
		case SDL_MOUSEBUTTONDOWN:
            Rml->context->ProcessMouseButtonDown(SystemInterface->TranslateMouseButton(event->button.button), SystemInterface->GetKeyModifiers());
            //if we clicked an element, end the event.
			hover = Rml->context->GetHoverElement();
			if(hover && (!has(hover->GetId(), "iframe_")))
				return true;
			break;
        case SDL_MOUSEBUTTONUP:
            Rml->context->ProcessMouseButtonUp(SystemInterface->TranslateMouseButton(event->button.button), SystemInterface->GetKeyModifiers());
			//if we clicked an element, end the event.
			hover = Rml->context->GetHoverElement();
			if(hover && (!has(hover->GetId(), "iframe_"))){
				//return true;
			}
			break;
        case SDL_MOUSEWHEEL:
            Rml->context->ProcessMouseWheel(event->wheel.y * -1, SystemInterface->GetKeyModifiers());
            break;
#ifdef ANDROID
        case SDL_KEYDOWN:
			//INFO("SDLRml::SDL_KEYDOWN("+toString((int)event->key.keysym.sym)+")\n");
			Rml->context->ProcessKeyDown(SystemInterface->TranslateKey(event->key.keysym.sym), SystemInterface->GetKeyModifiers());
			if(event->key.keysym.sym == 13) //enter
				Rml->context->ProcessTextInput("\n");
            break;
#else
		case SDL_KEYDOWN:{
			//INFO("SDLWindow::SDL_KEYDOWN("+toString(event->key.keysym.sym)+")\n");
			/*
			if(event->key.keysym.sym == 0){ return true; }
			if(event->key.keysym.sym > 96 && event->key.keysym.sym < 123){ //letter
				if(event->key.keysym.mod & KMOD_SHIFT && event->key.keysym.mod & KMOD_CAPS){ //both = lowercase
					//Event::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym]));
					Rml->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
				}
				else if(event->key.keysym.mod & KMOD_SHIFT || event->key.keysym.mod & KMOD_CAPS){ //1 = uppercase
					//Event::SendEvent("window", "keypress", toString(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]));
					Rml->context->ProcessTextInput(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]);
				}
				else{
					//Event::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym])); //lowercase
					Rml->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
				}
			}
			else if(event->key.keysym.mod & KMOD_SHIFT){ //other character keys
				//Event::SendEvent("window", "keypress", toString(SDLWindow::sdlShiftCharCode[event->key.keysym.sym])); //shifted symbol
				Rml->context->ProcessTextInput(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]);
			}
			else{
				//Event::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym])); //symbol
				Rml->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
			}
			*/
			//Event::SendEvent("window", "keydown", toString(SDLWindow::sdlKeyCode[event->key.keysym.sym])); //keycode
			//Rml->context->ProcessKeyDown((Rml::Input::KeyIdentifier)SDLWindow::sdlKeyCode[event->key.keysym.sym], SystemInterface->GetKeyModifiers());
			Rml->context->ProcessKeyDown(SystemInterface->TranslateKey(event->key.keysym.sym), SystemInterface->GetKeyModifiers());
			//TODO: If enter is pressed, send enter event on ProcessTextInput
			if(event->key.keysym.sym == 13) //Enter key
			//Rml->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]); //TEST
			Rml->context->ProcessTextInput("\n"); //TEST2
			return false; //allow event to continue
		}
#endif
		case SDL_TEXTINPUT:
			//INFO("SDLRml::SDL_TEXTINPUT("+String(event->text.text)+")\n");
			Rml->context->ProcessTextInput(event->text.text);
			break;
		case SDL_TEXTEDITING:
			//INFO("SDLRml::SDL_TEXTEDITING()\n");
			break;	
		case SDL_KEYUP:
			//Rml->context->ProcessKeyUp((Rml::Input::KeyIdentifier)SDLWindow::sdlKeyCode[event->key.keysym.sym], SystemInterface->GetKeyModifiers());
			Rml->context->ProcessKeyUp(SystemInterface->TranslateKey(event->key.keysym.sym), SystemInterface->GetKeyModifiers());
			break;
            default:
                break;
		} 
	return false; //allow event to continue
}

void SDLRml::Render(){
    //DEBUGFUNC();
	if(SdlWindow->width != Rml->context->GetDimensions().x || SdlWindow->height != Rml->context->GetDimensions().y){
		Rml->context->SetDimensions(Rml::Vector2i(SdlWindow->width, SdlWindow->height));
		// Reset blending and draw a fake point just outside the screen to let SDL know that it needs to reset its state in case it wants to render a texture 
		SDL_SetRenderDrawBlendMode(SdlWindow->renderer, SDL_BLENDMODE_NONE);
		SDL_RenderDrawPoint(SdlWindow->renderer, -1, -1);
	}
	Rml->context->Render();
}

void SDLRml::Update(){
	Rml->context->Update();
}
