// https://github.com/mikke89/RmlUi
// https://mikke89.github.io/RmlUiDoc/

#pragma once
#ifndef RmlMain_H
#define RmlMain_H

#include <RmlUi/Core.h>
//#include "DKWindow/DKWindow.h"
#include "RmlFile.h"
//#include "RmlMain/RmlMainConverter.h"

class RmlMain : public Rml::EventListener
{
public:
	bool Init();
	bool End();
	static RmlMain* Get();
	bool GetSourceCode(Rml::String& source_code);
	bool LoadFont(const Rml::String& file);
	bool LoadFonts(Rml::String& directory);
	bool LoadUrl(const Rml::String& url);
	bool LoadHtml(const Rml::String& html);
	void ProcessEvent(Rml::Event& rmlEvent); //overwritten
	bool RegisterEvent(const Rml::String& elementAddress, const Rml::String& type);
	bool SendEvent(const Rml::String& elementAddress, const Rml::String& type, const Rml::String& value);
	bool DebuggerOff();
	bool DebuggerOn();
	bool DebuggerToggle();
	bool UnregisterEvent(const Rml::String& elementAddress, const Rml::String& type);
	static Rml::Event* addressToEvent(const Rml::String& address);
	static Rml::String eventToAddress(Rml::Event* event);
	static Rml::Element* addressToElement(const Rml::String& address);
	static Rml::String elementToAddress(Rml::Element* element);
	Rml::String href;
	Rml::String protocol;
	Rml::String _path;
	Rml::String workingPath;
	Rml::Context* context;
	Rml::ElementDocument* document;
	Rml::Element* hover;

	static RmlMain* rmlMain;
	static RmlFile* rmlFile;
};

#endif //RmlMain_H
