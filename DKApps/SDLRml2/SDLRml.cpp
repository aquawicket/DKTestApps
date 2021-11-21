#include "SDL.h"
#include "RmlFile.h"
#include "SDLRml.h"
#include "RmlUtility.h"


SDLRml::SDLRml()
{
	//return this;
}

bool SDLRml::Init(){
	//Android SDL_TEXTINPUT events not working
	//SDL_StartTextInput(); 
	//SDL_EventState(SDL_TEXTINPUT, SDL_ENABLE);
	
	sdlWindow = SDLWindow::Get();
	rmlMain = RmlMain::Get();
	if(!sdlWindow || !rmlMain)
		return ERROR("SDLRml::Init(): INVALID OBJECTS\n");
#ifdef RML_SHELL_RENDER
	renderer = new ShellRenderInterfaceOpenGL();
#else
	renderer = new SDLRmlRenderer(sdlWindow->renderer, sdlWindow->window);
#endif
	systemInterface = new SDLRmlSystem();
	Rml::SetRenderInterface(renderer);
    Rml::SetSystemInterface(systemInterface);
	SDLWindow::AddEventFunc(&SDLRml::Handle, this);
	SDLWindow::AddRenderFunc(&SDLRml::Render, this);
	SDLWindow::AddUpdateFunc(&SDLRml::Update, this);
	return true;
}

bool SDLRml::End(){
	return true;
}

bool SDLRml::Handle(SDL_Event *event) {
	if(!rmlMain->document)
		return ERROR("rmlMain->document invalid");
	Rml::Element* hover;
	switch(event->type){
		case SDL_MOUSEMOTION:
			rmlMain->context->ProcessMouseMove(event->motion.x, event->motion.y, systemInterface->GetKeyModifiers());
			//if we clicked an element, end the event.
			hover = rmlMain->context->GetHoverElement();
			if(hover && (!RmlUtility::stringContains(hover->GetId(), "iframe_")))
				return true;
            break;   
		case SDL_MOUSEBUTTONDOWN:
            rmlMain->context->ProcessMouseButtonDown(systemInterface->TranslateMouseButton(event->button.button), systemInterface->GetKeyModifiers());
            //if we clicked an element, end the event.
			hover = rmlMain->context->GetHoverElement();
			if(hover && (!RmlUtility::stringContains(hover->GetId(), "iframe_")))
				return true;
			break;
        case SDL_MOUSEBUTTONUP:
            rmlMain->context->ProcessMouseButtonUp(systemInterface->TranslateMouseButton(event->button.button), systemInterface->GetKeyModifiers());
			//if we clicked an element, end the event.
			hover = rmlMain->context->GetHoverElement();
			if(hover && (!RmlUtility::stringContains(hover->GetId(), "iframe_"))){
				//return true;
			}
			break;
        case SDL_MOUSEWHEEL:
            rmlMain->context->ProcessMouseWheel(event->wheel.y * -1, systemInterface->GetKeyModifiers());
            break;
#ifdef ANDROID
        case SDL_KEYDOWN:
			//RMLINFO("SDLRml::SDL_KEYDOWN("+toString((int)event->key.keysym.sym)+")\n");
			rmlMain->context->ProcessKeyDown(systemInterface->TranslateKey(event->key.keysym.sym), systemInterface->GetKeyModifiers());
			if(event->key.keysym.sym == 13) //enter
				rmlMain->context->ProcessTextInput("\n");
            break;
#else
		case SDL_KEYDOWN:{
			//RMLINFO("SDLWindow::SDL_KEYDOWN("+toString(event->key.keysym.sym)+")\n");
			/*
			if(event->key.keysym.sym == 0){ return true; }
			if(event->key.keysym.sym > 96 && event->key.keysym.sym < 123){ //letter
				if(event->key.keysym.mod & KMOD_SHIFT && event->key.keysym.mod & KMOD_CAPS){ //both = lowercase
					//RmlEvent::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym]));
					rmlMain->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
				}
				else if(event->key.keysym.mod & KMOD_SHIFT || event->key.keysym.mod & KMOD_CAPS){ //1 = uppercase
					//RmlEvent::SendEvent("window", "keypress", toString(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]));
					rmlMain->context->ProcessTextInput(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]);
				}
				else{
					//RmlEvent::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym])); //lowercase
					rmlMain->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
				}
			}
			else if(event->key.keysym.mod & KMOD_SHIFT){ //other character keys
				//RmlEvent::SendEvent("window", "keypress", toString(SDLWindow::sdlShiftCharCode[event->key.keysym.sym])); //shifted symbol
				rmlMain->context->ProcessTextInput(SDLWindow::sdlShiftCharCode[event->key.keysym.sym]);
			}
			else{
				//RmlEvent::SendEvent("window", "keypress", toString(SDLWindow::sdlCharCode[event->key.keysym.sym])); //symbol
				rmlMain->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]);
			}
			*/
			//RmlEvent::SendEvent("window", "keydown", toString(SDLWindow::sdlKeyCode[event->key.keysym.sym])); //keycode
			//rmlMain->context->ProcessKeyDown((Rml::Input::KeyIdentifier)SDLWindow::sdlKeyCode[event->key.keysym.sym], systemInterface->GetKeyModifiers());
			rmlMain->context->ProcessKeyDown(systemInterface->TranslateKey(event->key.keysym.sym), systemInterface->GetKeyModifiers());
			//TODO: If enter is pressed, send enter event on ProcessTextInput
			if(event->key.keysym.sym == 13) //Enter key
			//rmlMain->context->ProcessTextInput(SDLWindow::sdlCharCode[event->key.keysym.sym]); //TEST
			rmlMain->context->ProcessTextInput("\n"); //TEST2
			return false; //allow event to continue
		}
#endif
		case SDL_TEXTINPUT:
			//RMLINFO("SDLRml::SDL_TEXTINPUT("+String(event->text.text)+")\n");
			rmlMain->context->ProcessTextInput(event->text.text);
			break;
		case SDL_TEXTEDITING:
			//RMLINFO("SDLRml::SDL_TEXTEDITING()\n");
			break;	
		case SDL_KEYUP:
			//rmlMain->context->ProcessKeyUp((Rml::Input::KeyIdentifier)SDLWindow::sdlKeyCode[event->key.keysym.sym], systemInterface->GetKeyModifiers());
			rmlMain->context->ProcessKeyUp(systemInterface->TranslateKey(event->key.keysym.sym), systemInterface->GetKeyModifiers());
			break;
            default:
                break;
		} 
	return false; //allow event to continue
}

void SDLRml::Render(){
    //DEBUGFUNC();
	if(sdlWindow->width != rmlMain->context->GetDimensions().x || sdlWindow->height != rmlMain->context->GetDimensions().y){
		rmlMain->context->SetDimensions(Rml::Vector2i(sdlWindow->width, sdlWindow->height));
		// Reset blending and draw a fake point just outside the screen to let SDL know that it needs to reset its state in case it wants to render a texture 
		SDL_SetRenderDrawBlendMode(sdlWindow->renderer, SDL_BLENDMODE_NONE);
		SDL_RenderDrawPoint(sdlWindow->renderer, -1, -1);
	}
	rmlMain->context->Render();
}

void SDLRml::Update(){
	rmlMain->context->Update();
}
