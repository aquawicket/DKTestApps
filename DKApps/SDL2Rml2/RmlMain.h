/*
* This source file is part of digitalknob, the cross-platform C/C++/Javascript/Html/Css Solution
*
* For the latest information, see https://github.com/aquawicket/DigitalKnob
*
* Copyright(c) 2010 - 2022 Digitalknob Team, and contributors
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright noticeand this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

// https://github.com/mikke89/RmlUi
// https://mikke89.github.io/RmlUiDoc/

#pragma once
#ifndef RmlMain_H
#define RmlMain_H

#include <RmlUi/Core.h>
//#include "RmlWindow/RmlWindow.h"
#include "RmlFile.h"
//#include "RmlMain/RmlMainConverter.h"

class RmlMain : public Rml::EventListener
{
public:
	RmlMain();
	~RmlMain();
	static RmlMain* Get();
	//bool GetSourceCode(Rml::String& source_code);
	bool LoadFont(const Rml::String& file);
	bool LoadFonts(Rml::String& directory);
	bool LoadUrl(const Rml::String& url);
	bool LoadHtml(const Rml::String& html);
	//void ProcessEvent(Rml::Event& rmlEvent); //overwritten
	//bool RegisterEvent(const Rml::String& elementAddress, const Rml::String& type);
	//bool SendEvent(const Rml::String& elementAddress, const Rml::String& type, const Rml::String& value);
	bool DebuggerOff();
	bool DebuggerOn();
	bool DebuggerToggle();
	//bool UnregisterEvent(const Rml::String& elementAddress, const Rml::String& type);
	//static Rml::Event* addressToEvent(const Rml::String& address);
	//static Rml::String eventToAddress(Rml::Event* event);
	//static Rml::Element* addressToElement(const Rml::String& address);
	//static Rml::String elementToAddress(Rml::Element* element);
	Rml::String href;
	//Rml::String protocol;
	Rml::String _path;
	Rml::String workingPath;
	Rml::Context* context;
	Rml::ElementDocument* document;
	Rml::Element* hover;

	static RmlMain* rmlMain;
	static RmlFile* rmlFile;
};

#endif //RmlMain_H
