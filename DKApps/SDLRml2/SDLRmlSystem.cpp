#include <RmlUi/Core.h>
#include "SDLRmlSystem.h"
#include "RmlUtility.h"

Rml::Input::KeyIdentifier SDLRmlSystem::TranslateKey(SDL_Keycode sdlkey){
    switch(sdlkey) {
        case SDLK_UNKNOWN:
            return Rml::Input::KI_UNKNOWN;
            break;
        case SDLK_SPACE:
            return Rml::Input::KI_SPACE;
            break;
        case SDLK_0:
            return Rml::Input::KI_0;
            break;
        case SDLK_1:
            return Rml::Input::KI_1;
            break;
        case SDLK_2:
            return Rml::Input::KI_2;
            break;
        case SDLK_3:
            return Rml::Input::KI_3;
            break;
        case SDLK_4:
            return Rml::Input::KI_4;
            break;
        case SDLK_5:
            return Rml::Input::KI_5;
            break;
        case SDLK_6:
            return Rml::Input::KI_6;
            break;
        case SDLK_7:
            return Rml::Input::KI_7;
            break;
        case SDLK_8:
            return Rml::Input::KI_8;
            break;
        case SDLK_9:
            return Rml::Input::KI_9;
            break;
        case SDLK_a:
            return Rml::Input::KI_A;
            break;
        case SDLK_b:
            return Rml::Input::KI_B;
            break;
        case SDLK_c:
            return Rml::Input::KI_C;
            break;
        case SDLK_d:
            return Rml::Input::KI_D;
            break;
        case SDLK_e:
            return Rml::Input::KI_E;
            break;
        case SDLK_f:
            return Rml::Input::KI_F;
            break;
        case SDLK_g:
            return Rml::Input::KI_G;
            break;
        case SDLK_h:
            return Rml::Input::KI_H;
            break;
        case SDLK_i:
            return Rml::Input::KI_I;
            break;
        case SDLK_j:
            return Rml::Input::KI_J;
            break;
        case SDLK_k:
            return Rml::Input::KI_K;
            break;
        case SDLK_l:
            return Rml::Input::KI_L;
            break;
        case SDLK_m:
            return Rml::Input::KI_M;
            break;
        case SDLK_n:
            return Rml::Input::KI_N;
            break;
        case SDLK_o:
            return Rml::Input::KI_O;
            break;
        case SDLK_p:
            return Rml::Input::KI_P;
            break;
        case SDLK_q:
            return Rml::Input::KI_Q;
            break;
        case SDLK_r:
            return Rml::Input::KI_R;
            break;
        case SDLK_s:
            return Rml::Input::KI_S;
            break;
        case SDLK_t:
            return Rml::Input::KI_T;
            break;
        case SDLK_u:
            return Rml::Input::KI_U;
            break;
        case SDLK_v:
            return Rml::Input::KI_V;
            break;
        case SDLK_w:
            return Rml::Input::KI_W;
            break;
        case SDLK_x:
            return Rml::Input::KI_X;
            break;
        case SDLK_y:
            return Rml::Input::KI_Y;
            break;
        case SDLK_z:
            return Rml::Input::KI_Z;
            break;
        case SDLK_SEMICOLON:
            return Rml::Input::KI_OEM_1;
            break;
        case SDLK_QUOTE:
            return Rml::Input::KI_OEM_7;
            break;
        case SDLK_EQUALS:
            return Rml::Input::KI_OEM_PLUS;
            break;
        case SDLK_PLUS:
            return Rml::Input::KI_OEM_PLUS;
            break;
        case SDLK_COMMA:
            return Rml::Input::KI_OEM_COMMA;
            break;
        case SDLK_MINUS:
            return Rml::Input::KI_OEM_MINUS;
            break;
        case SDLK_PERIOD:
            return Rml::Input::KI_OEM_PERIOD;
            break;
        case SDLK_SLASH:
            return Rml::Input::KI_OEM_2;
            break;
        case SDLK_BACKQUOTE:
            return Rml::Input::KI_OEM_3;
            break;
        case SDLK_LEFTBRACKET:
            return Rml::Input::KI_OEM_4;
            break;
        case SDLK_BACKSLASH:
            return Rml::Input::KI_OEM_5;
            break;
        case SDLK_RIGHTBRACKET:
            return Rml::Input::KI_OEM_6;
            break;
        case SDLK_QUOTEDBL:
            return Rml::Input::KI_OEM_7;
            break;
        case SDLK_ESCAPE:
            return Rml::Input::KI_ESCAPE;
            break;
        case SDLK_KP_0:
            return Rml::Input::KI_NUMPAD0;
            break;
        case SDLK_KP_1:
            return Rml::Input::KI_NUMPAD1;
            break;
        case SDLK_KP_2:
            return Rml::Input::KI_NUMPAD2;
            break;
        case SDLK_KP_3:
            return Rml::Input::KI_NUMPAD3;
            break;
        case SDLK_KP_4:
            return Rml::Input::KI_NUMPAD4;
            break;
        case SDLK_KP_5:
            return Rml::Input::KI_NUMPAD5;
            break;
        case SDLK_KP_6:
            return Rml::Input::KI_NUMPAD6;
            break;
        case SDLK_KP_7:
            return Rml::Input::KI_NUMPAD7;
            break;
        case SDLK_KP_8:
            return Rml::Input::KI_NUMPAD8;
            break;
        case SDLK_KP_9:
            return Rml::Input::KI_NUMPAD9;
            break;
        case SDLK_KP_ENTER:
            return Rml::Input::KI_NUMPADENTER;
            break;
        case SDLK_KP_MULTIPLY:
            return Rml::Input::KI_MULTIPLY;
            break;
        case SDLK_KP_PLUS:
            return Rml::Input::KI_ADD;
            break;
        case SDLK_KP_MINUS:
            return Rml::Input::KI_SUBTRACT;
            break;
        case SDLK_KP_PERIOD:
            return Rml::Input::KI_DECIMAL;
            break;
        case SDLK_KP_DIVIDE:
            return Rml::Input::KI_DIVIDE;
            break;
        case SDLK_KP_EQUALS:
            return Rml::Input::KI_OEM_NEC_EQUAL;
            break;
        case SDLK_BACKSPACE:
            return Rml::Input::KI_BACK;
            break;
        case SDLK_TAB:
            return Rml::Input::KI_TAB;
            break;
        case SDLK_CLEAR:
            return Rml::Input::KI_CLEAR;
            break;
        case SDLK_RETURN:
            return Rml::Input::KI_RETURN;
            break;
        case SDLK_PAUSE:
            return Rml::Input::KI_PAUSE;
            break;
        case SDLK_CAPSLOCK:
            return Rml::Input::KI_CAPITAL;
            break;
        case SDLK_PAGEUP:
            return Rml::Input::KI_PRIOR;
            break;
        case SDLK_PAGEDOWN:
            return Rml::Input::KI_NEXT;
            break;
        case SDLK_END:
            return Rml::Input::KI_END;
            break;
        case SDLK_HOME:
            return Rml::Input::KI_HOME;
            break;
        case SDLK_LEFT:
            return Rml::Input::KI_LEFT;
            break;
        case SDLK_UP:
            return Rml::Input::KI_UP;
            break;
        case SDLK_RIGHT:
            return Rml::Input::KI_RIGHT;
            break;
        case SDLK_DOWN:
            return Rml::Input::KI_DOWN;
            break;
        case SDLK_INSERT:
            return Rml::Input::KI_INSERT;
            break;
        case SDLK_DELETE:
            return Rml::Input::KI_DELETE;
            break;
        case SDLK_HELP:
            return Rml::Input::KI_HELP;
            break;
        case SDLK_F1:
            return Rml::Input::KI_F1;
            break;
        case SDLK_F2:
            return Rml::Input::KI_F2;
            break;
        case SDLK_F3:
            return Rml::Input::KI_F3;
            break;
        case SDLK_F4:
            return Rml::Input::KI_F4;
            break;
        case SDLK_F5:
            return Rml::Input::KI_F5;
            break;
        case SDLK_F6:
            return Rml::Input::KI_F6;
            break;
        case SDLK_F7:
            return Rml::Input::KI_F7;
            break;
        case SDLK_F8:
            return Rml::Input::KI_F8;
            break;
        case SDLK_F9:
            return Rml::Input::KI_F9;
            break;
        case SDLK_F10:
            return Rml::Input::KI_F10;
            break;
        case SDLK_F11:
            return Rml::Input::KI_F11;
            break;
        case SDLK_F12:
            return Rml::Input::KI_F12;
            break;
        case SDLK_F13:
            return Rml::Input::KI_F13;
            break;
        case SDLK_F14:
            return Rml::Input::KI_F14;
            break;
        case SDLK_F15:
            return Rml::Input::KI_F15;
            break;
        case SDLK_NUMLOCKCLEAR:
            return Rml::Input::KI_NUMLOCK;
            break;
        case SDLK_PRINTSCREEN:
            return Rml::Input::KI_SNAPSHOT;
            break;
        case SDLK_SCROLLLOCK:
            return Rml::Input::KI_SCROLL;
            break;
        case SDLK_LSHIFT:
            return Rml::Input::KI_LSHIFT;
            break;
        case SDLK_RSHIFT:
            return Rml::Input::KI_RSHIFT;
            break;
        case SDLK_LCTRL:
            return Rml::Input::KI_LCONTROL;
            break;
        case SDLK_RCTRL:
            return Rml::Input::KI_RCONTROL;
            break;
        case SDLK_LALT:
            return Rml::Input::KI_LMENU;
            break;
        case SDLK_RALT:
            return Rml::Input::KI_RMENU;
            break;
        case SDLK_LGUI:
            return Rml::Input::KI_LMETA;
            break;
        case SDLK_RGUI:
            return Rml::Input::KI_RMETA;
            break;
        /*case SDLK_LSUPER:
            return Rml::Input::KI_LWIN;
            break;
        case SDLK_RSUPER:
            return Rml::Input::KI_RWIN;
            break;*/
        default:
            return Rml::Input::KI_UNKNOWN;
            break;
    }
}

int SDLRmlSystem::TranslateMouseButton(Uint8 button){
    switch(button){
        case SDL_BUTTON_LEFT:
            return 0;
        case SDL_BUTTON_RIGHT:
            return 1;
        case SDL_BUTTON_MIDDLE:
            return 2;
        case SDL_BUTTON(3):
            return 3;
        case SDL_BUTTON(4):
            return 4;
        case SDL_BUTTON(5):
            return 5;
        case SDL_BUTTON(6):
            return 6;
        default:
            return 99; //FIXME
    }
}

int SDLRmlSystem::GetKeyModifiers(){
    SDL_Keymod sdlMods = SDL_GetModState();
    int retval = 0;
    if(sdlMods & KMOD_CTRL)
        retval |= Rml::Input::KM_CTRL;
    if(sdlMods & KMOD_SHIFT)
        retval |= Rml::Input::KM_SHIFT;
    if(sdlMods & KMOD_ALT)
        retval |= Rml::Input::KM_ALT;
	if(sdlMods & KMOD_NUM)
        retval |= Rml::Input::KM_NUMLOCK;
    return retval;
}

double SDLRmlSystem::GetElapsedTime(){
	return (float)SDL_GetTicks() / 1000;
}

bool SDLRmlSystem::LogMessage(Rml::Log::Type type, const Rml::String& message){
	if(RmlUtility::stringContains(message,"Loaded font face"))
		type = Rml::Log::LT_DEBUG;
	switch(type){
	case Rml::Log::LT_ALWAYS:
		RMLINFO("[Rml] "+Rml::String(message)+"\n");
		break;
	case Rml::Log::LT_ERROR:
		RMLERROR("[Rml] "+Rml::String(message)+"\n");
		break;
	case Rml::Log::LT_ASSERT:
		RMLASSERT("[Rml] "+Rml::String(message)+"\n");
		break;
	case Rml::Log::LT_WARNING:
		RMLWARN("[Rml] "+Rml::String(message)+"\n");
		break;
	case Rml::Log::LT_INFO:
		RMLINFO("[Rml] "+Rml::String(message)+"\n");
		break;
	case Rml::Log::LT_DEBUG:
		RMLDEBUG("[Rml] "+Rml::String(message)+"\n");
		break;
    case Rml::Log::LT_MAX:
        RMLVERBOSE("[Rml] "+Rml::String(message)+"\n");
        break;
	};
	return true;
};