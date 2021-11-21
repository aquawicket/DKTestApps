//TODO - add SFMLWindow to all functions

//#include "RmlAndroid.h"
#include "RmlWindow.h"

bool RmlWindow::Init()
{
	RmlClass::RmlCreate("RmlWindowJS");
	RmlClass::RmlCreate("RmlWindowV8");
	return true;
}

bool RmlWindow::End()
{
	return true;
}



///
///  If "RmlWindow::TestInt()" calls a registered function, it will alter the variable and send it back.
///  \a see: SDLWindow.h
bool RmlWindow::TestInt(int& input, int& output)
{
	if(RmlClass::HasFunc("SDLWindow::TestInt")){
		return RmlClass::CallFunc("SDLWindow::TestInt", &input, &output);
	}
	if(RmlClass::HasFunc("SFMLWindow::TestInt")){
		return RmlClass::CallFunc("SFMLWindow::TestInt", &input, &output);
	}
	RMLWARN("RmlWindow::TestInt(): No function available\n");
	return false;
}

///
///  If "RmlWindow::TestString()" calls a registered function, it will alter the variable and send it back.
///  \a see: SDLWindow.h
bool RmlWindow::TestString(std::string& input, std::string& output)
{
	if(RmlClass::HasFunc("SDLWindow::TestString")){
		return RmlClass::CallFunc("SDLWindow::TestString", &input, &output);
	}
	if(RmlClass::HasFunc("SFMLWindow::TestString")){
		return RmlClass::CallFunc("SFMLWindow::TestString", &input, &output);
	}
	RMLWARN("RmlWindow::TestString(): No function available\n");
	return false;
}

///
///  If "RmlWindow::TestReturnInt()" calls a registered function, it will return a variable.
///  \a see: SDLWindow.h
bool RmlWindow::TestReturnInt(int& output)
{
	if(RmlClass::HasFunc("SDLWindow::TestReturnInt")){
		return RmlClass::CallFunc("SDLWindow::TestReturnInt", NULL, &output);
	}
	if(RmlClass::HasFunc("SFMLWindow::TestReturnInt")){
		return RmlClass::CallFunc("SFMLWindow::TestReturnInt", NULL, &output);
	}
	RMLWARN("RmlWindow::TestReturnInt(): No function available\n");
	return false;
}

///
///  If "RmlWindow::TestReturnString()" calls a registered function, it will return a variable.
///  \a see: SDLWindow.h
bool RmlWindow::TestReturnString(std::string& output)
{
	if(RmlClass::HasFunc("SDLWindow::TestReturnString")){
		return RmlClass::CallFunc("SDLWindow::TestReturnString", NULL, &output);
	}
	if(RmlClass::HasFunc("SFMLWindow::TestReturnString")){
		return RmlClass::CallFunc("SFMLWindow::TestReturnString", NULL, &output);
	}
	RMLWARN("RmlWindow::TestReturnString(): No function available\n");
	return false;
}

bool RmlWindow::Create()
{
	if(RmlClass::RmlAvailable("SDLWindow")){
		RmlClass::RmlCreate("SDLWindow");
		return true;
	}
	else if(RmlClass::RmlAvailable("SFMLWindow")){
		RmlClass::RmlCreate("SFMLWindow");
		return true;
	}
	else if(RmlClass::RmlAvailable("OSGWindow")){
		RmlClass::RmlCreate("OSGWindow");
		return true;
	}
	else{
		RMLWARN("RmlWindow::Init(): No window system available\n");
	}
	return false;
}

bool RmlWindow::Fullscreen()
{
	if(RmlClass::HasFunc("CefWindow::Fullscreen")){
		return RmlClass::CallFunc("CefWindow::Fullscreen", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Fullscreen")){
		return RmlClass::CallFunc("SDLWindow::Fullscreen", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Fullscreen")){
		return RmlClass::CallFunc("OSGWindow::Fullscreen", NULL, NULL);
	}
	RMLWARN("RmlWindow::Fullscreen(): No function available\n");
	return false;
}

bool RmlWindow::GetHandle(void*& handle)
{
	//EXAMPLE
	//HWND hwnd = NULL;
	//RmlWindow::GetHandle((void*&)hwnd);
	
	if(RmlClass::HasFunc("CefWindow::GetHandle")){
		return RmlClass::CallFunc("CefWindow::GetHandle", NULL, &handle);
	}
	if(RmlClass::HasFunc("SDLWindow::GetHandle")){
		return RmlClass::CallFunc("SDLWindow::GetHandle", NULL, &handle);
	}
	if(RmlClass::HasFunc("OSGWindow::GetHandle")){
		return RmlClass::CallFunc("OSGWindow::GetHandle", NULL, &handle);
	}
	RMLWARN("RmlWindow::GetHandle(): No function available\n");
	return false;
}

bool RmlWindow::GetHeight(int& height)
{
	if(RmlClass::HasFunc("CefWindow::GetHeight")){
		return RmlClass::CallFunc("CefWindow::GetHeight", NULL, &height);
	}
	if(RmlClass::HasFunc("SDLWindow::GetHeight")){
		return RmlClass::CallFunc("SDLWindow::GetHeight", NULL, &height);
	}
	if(RmlClass::HasFunc("OSGWindow::GetHeight")){
		return RmlClass::CallFunc("OSGWindow::GetHeight", NULL, &height);
	}
	RMLWARN("RmlWindow::GetHeight(): No function available\n");
	return false;
}

bool RmlWindow::GetMouseX(int& x)
{
	if(RmlClass::HasFunc("CefWindow::GetMouseX")){
		return RmlClass::CallFunc("CefWindow::GetMouseX", NULL, &x);
	}
	if(RmlClass::HasFunc("SDLWindow::GetMouseX")){
		return RmlClass::CallFunc("SDLWindow::GetMouseX", NULL, &x);
	}
	if(RmlClass::HasFunc("OSGWindow::GetMouseX")){
		return RmlClass::CallFunc("OSGWindow::GetMouseX", NULL, &x);
	}
	RMLWARN("RmlWindow::GetMouseX(): No function available\n");
	return false;
}

bool RmlWindow::GetMouseY(int& y)
{
	if(RmlClass::HasFunc("CefWindow::GetMouseY")){
		return RmlClass::CallFunc("CefWindow::GetMouseY", NULL, &y);
	}
	if(RmlClass::HasFunc("SDLWindow::GetMouseY")){
		return RmlClass::CallFunc("SDLWindow::GetMouseY", NULL, &y);
	}
	if(RmlClass::HasFunc("OSGWindow::GetMouseY")){
		return RmlClass::CallFunc("OSGWindow::GetMouseY", NULL, &y);
	}
	RMLWARN("RmlWindow::GetMouseY(): No function available\n");
	return false;
}

bool RmlWindow::GetPixelRatio(float& ratio)
{
	if(RmlClass::HasFunc("CefWindow::GetPixelRatio")){
		return RmlClass::CallFunc("CefWindow::GetPixelRatio", NULL, &ratio);
	}
	if(RmlClass::HasFunc("SDLWindow::GetPixelRatio")){
		return RmlClass::CallFunc("SDLWindow::GetPixelRatio", NULL, &ratio);
	}
	if(RmlClass::HasFunc("OSGWindow::GetPixelRatio")){
		return RmlClass::CallFunc("OSGWindow::GetPixelRatio", NULL, &ratio);
	}
	RMLWARN("RmlWindow::GetPixelRatio(): No function available\n");
	ratio = 1.0;
	return false;
}

bool RmlWindow::GetTitle(std::string& title)
{
	if(RmlClass::HasFunc("CefWindow::GetTitle")){
		return RmlClass::CallFunc("CefWindow::GetTitle", NULL, &title);
	}
	if(RmlClass::HasFunc("SDLWindow::GetTitle")){
		return RmlClass::CallFunc("SDLWindow::GetTitle", NULL, &title);
	}
	if(RmlClass::HasFunc("OSGWindow::GetTitle")){
		return RmlClass::CallFunc("OSGWindow::GetTitle", NULL, &title);
	}
	RMLWARN("RmlWindow::GetTitle(): No function available\n");
	return false;
}

bool RmlWindow::GetWidth(int& width)
{
	if(RmlClass::HasFunc("CefWindow::GetWidth")){
		return RmlClass::CallFunc("CefWindow::GetWidth", NULL, &width);
	}
	if(RmlClass::HasFunc("SDLWindow::GetWidth")){
		return RmlClass::CallFunc("SDLWindow::GetWidth", NULL, &width);
	}
	if(RmlClass::HasFunc("OSGWindow::GetWidth")){
		return RmlClass::CallFunc("OSGWindow::GetWidth", NULL, &width);
	}
	RMLWARN("RmlWindow::GetWidth(): No function available\n");
	return false;
}

bool RmlWindow::GetX(int& x)
{
	if(RmlClass::HasFunc("CefWindow::GetX")){
		return RmlClass::CallFunc("CefWindow::GetX", NULL, &x);
	}
	if(RmlClass::HasFunc("SDLWindow::GetX")){
		return RmlClass::CallFunc("SDLWindow::GetX", NULL, &x);
	}
	if(RmlClass::HasFunc("OSGWindow::GetX")){
		return RmlClass::CallFunc("OSGWindow::GetX", NULL, &x);
	}
	RMLWARN("RmlWindow::GetX(): No function available\n");
	return false;
}

bool RmlWindow::GetY(int& y)
{
	if(RmlClass::HasFunc("CefWindow::GetY")){
		return RmlClass::CallFunc("CefWindow::GetY", NULL, &y);
	}
	if(RmlClass::HasFunc("SDLWindow::GetY")){
		return RmlClass::CallFunc("SDLWindow::GetY", NULL, &y);
	}
	if(RmlClass::HasFunc("OSGWindow::GetY")){
		return RmlClass::CallFunc("OSGWindow::GetY", NULL, &y);
	}
	RMLWARN("RmlWindow::GetY(): No function available\n");
	return false;
}

bool RmlWindow::Hide()
{
	if(RmlClass::HasFunc("CefWindow::Hide")){
		return RmlClass::CallFunc("CefWindow::Hide", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Hide")){
		return RmlClass::CallFunc("SDLWindow::Hide", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Hide")){
		return RmlClass::CallFunc("OSGWindow::Hide", NULL, NULL);
	}
	RMLWARN("RmlWindow::Hide(): No function available\n");
	return false;
}

bool RmlWindow::IsFullscreen(bool& fullscreen)
{
	if(RmlClass::HasFunc("CefWindow::IsFullscreen")){
		return RmlClass::CallFunc("CefWindow::IsFullscreen", NULL, &fullscreen);
	}
	if(RmlClass::HasFunc("SDLWindow::IsFullscreen")){
		return RmlClass::CallFunc("SDLWindow::IsFullscreen", NULL, &fullscreen);
	}
	if(RmlClass::HasFunc("OSGWindow::IsFullscreen")){
		return RmlClass::CallFunc("OSGWindow::IsFullscreen", NULL, &fullscreen);
	}
	RMLWARN("RmlWindow::IsFullscreen(): No function available\n");
	return false;
}

bool RmlWindow::IsVisible(bool& visible)
{
	if(RmlClass::HasFunc("CefWindow::IsVisible")){
		return RmlClass::CallFunc("CefWindow::IsVisible", NULL, &visible);
	}
	if(RmlClass::HasFunc("SDLWindow::IsVisible")){
		return RmlClass::CallFunc("SDLWindow::IsVisible", NULL, &visible);
	}
	if(RmlClass::HasFunc("OSGWindow::IsVisible")){
		return RmlClass::CallFunc("OSGWindow::IsVisible", NULL, &visible);
	}
	RMLWARN("RmlWindow::IsVisible(): No function available\n");
	return false;
}

bool RmlWindow::Maximize()
{
	if(RmlClass::HasFunc("CefWindow::Maximize")) {
		return RmlClass::CallFunc("CefWindow::Maximize", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Maximize")){
		return RmlClass::CallFunc("SDLWindow::Maximize", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Maximize")){
		return RmlClass::CallFunc("OSGWindow::Maximize", NULL, NULL);
	}
	RMLWARN("RmlWindow::Maximize(): No function available\n");
	return false;
}

bool RmlWindow::MessageBox(std::string& msg)
{
	if(RmlClass::HasFunc("CefWindow::MessageBox")){
		return RmlClass::CallFunc("CefWindow::MessageBox", &msg, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::MessageBox")){
		return RmlClass::CallFunc("SDLWindow::MessageBox", &msg, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::MessageBox")){
		return RmlClass::CallFunc("OSGWindow::MessageBox", &msg, NULL);
	}
	RMLWARN("RmlWindow::MessageBox(): No function available\n");
	return false;
}

bool RmlWindow::Minimize()
{
	if(RmlClass::HasFunc("CefWindow::Minimize")) {
		return RmlClass::CallFunc("CefWindow::Minimize", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Minimize")){
		return RmlClass::CallFunc("SDLWindow::Minimize", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Minimize")){
		return RmlClass::CallFunc("OSGWindow::Minimize", NULL, NULL);
	}
	RMLWARN("RmlWindow::Minimize(): No function available\n");
	return false;
}

bool RmlWindow::Restore()
{
	if(RmlClass::HasFunc("CefWindow::Restore")) {
		return RmlClass::CallFunc("CefWindow::Restore", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Restore")){
		return RmlClass::CallFunc("SDLWindow::Restore", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Restore")){
		return RmlClass::CallFunc("OSGWindow::Restore", NULL, NULL);
	}
	RMLWARN("RmlWindow::Restore(): No function available\n");
	return false;
}

bool RmlWindow::SetHeight(int& h)
{
	//if(RmlClass::HasFunc("CefWindow::SetHeight")){
	//	return RmlClass::CallFunc("CefWindow::SetHeight", &h, NULL);
	//}
	if(RmlClass::HasFunc("SDLWindow::SetHeight")){
		return RmlClass::CallFunc("SDLWindow::SetHeight", &h, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetHeight")){
		return RmlClass::CallFunc("OSGWindow::SetHeight", &h, NULL);
	}
	RMLWARN("RmlWindow::SetHeight(): No function available\n");
	return false;
}

bool RmlWindow::SetIcon(std::string& file)
{
	if(RmlClass::HasFunc("CefWindow::SetIcon")){
		return RmlClass::CallFunc("CefWindow::SetIcon", &file, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::SetIcon")){
		return RmlClass::CallFunc("SDLWindow::SetIcon", &file, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetIcon")){
		return RmlClass::CallFunc("OSGWindow::SetIcon", &file, NULL);
	}
	RMLWARN("RmlWindow::SetIcon(): No function available\n");
	return false;
}

bool RmlWindow::SetTitle(std::string& string)
{
	if(RmlClass::HasFunc("CefWindow::SetTitle")){
		return RmlClass::CallFunc("CefWindow::SetTitle", &string, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::SetTitle")){
		return RmlClass::CallFunc("SDLWindow::SetTitle", &string, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetTitle")){
		return RmlClass::CallFunc("OSGWindow::SetTitle", &string, NULL);
	}
	RMLWARN("RmlWindow::SetTitle(): No function available\n");
	return false;
}

bool RmlWindow::SetWidth(int& w)
{
	//if(RmlClass::HasFunc("CefWindow::SetWidth")){
	//	return RmlClass::CallFunc("CefWindow::SetWidth", &w, NULL);
	//}
	if(RmlClass::HasFunc("SDLWindow::SetWidth")){
		return RmlClass::CallFunc("SDLWindow::SetWidth", &w, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetWidth")){
		return RmlClass::CallFunc("OSGWindow::SetWidth", &w, NULL);
	}
	RMLWARN("RmlWindow::SetWidth(): No function available\n");
	return false;
}

bool RmlWindow::SetX(int& x)
{
	//if(RmlClass::HasFunc("CefWindow::SetX")){
	//	return RmlClass::CallFunc("CefWindow::SetX", &x, NULL);
	//}
	if(RmlClass::HasFunc("SDLWindow::SetX")){
		return RmlClass::CallFunc("SDLWindow::SetX", &x, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetX")){
		return RmlClass::CallFunc("OSGWindow::SetX", &x, NULL);
	}
	RMLWARN("RmlWindow::SetX(): No function available\n");
	return false;
}

bool RmlWindow::SetY(int& y)
{
	//if(RmlClass::HasFunc("CefWindow::SetY")){
	//	return RmlClass::CallFunc("CefWindow::SetY", &y, NULL);
	//}
	if(RmlClass::HasFunc("SDLWindow::SetY")){
		return RmlClass::CallFunc("SDLWindow::SetY", &y, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::SetY")){
		return RmlClass::CallFunc("OSGWindow::SetY", &y, NULL);
	}
	RMLWARN("RmlWindow::SetY(): No function available\n");
	return false;
}

bool RmlWindow::Show()
{
	if(RmlClass::HasFunc("CefWindow::Show")){
		return RmlClass::CallFunc("CefWindow::Show", NULL, NULL);
	}
	if(RmlClass::HasFunc("SDLWindow::Show")){
		return RmlClass::CallFunc("SDLWindow::Show", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Show")){
		return RmlClass::CallFunc("OSGWindow::Show", NULL, NULL);
	}
	RMLWARN("RmlWindow::Show(): No function available\n");
	return false;
}

bool RmlWindow::Windowed()
{
	if(RmlClass::HasFunc("SDLWindow::Windowed")){
		return RmlClass::CallFunc("SDLWindow::Windowed", NULL, NULL);
	}
	if(RmlClass::HasFunc("OSGWindow::Windowed")){
		return RmlClass::CallFunc("OSGWindow::Windowed", NULL, NULL);
	}
	RMLWARN("RmlWindow::Windowed(): No function available\n");
	return false;
}