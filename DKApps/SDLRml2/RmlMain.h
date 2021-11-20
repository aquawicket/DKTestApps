// https://github.com/mikke89/RmlUi
// https://mikke89.github.io/RmlUiDoc/

#pragma once
#ifndef RmlMain_H
#define RmlMain_H

#include <RmlUi/Core.h>
#include "DK/DK.h"
#include "DKWindow/DKWindow.h"
#include "RmlMain/RmlFile.h"
//#include "RmlMain/RmlMainConverter.h"

class RmlMain : public Rml::EventListener, public objectT<RmlMain> {
public:
	bool Init();
	bool End();
	bool GetSourceCode(std::string& source_code);
	bool LoadFont(const std::string& file);
	bool LoadFonts(std::string& directory);
	bool LoadUrl(const std::string& url);
	bool LoadHtml(const std::string& html);
	void ProcessEvent(Rml::Event& rmlEvent); //overwritten
	bool RegisterEvent(const std::string& elementAddress, const std::string& type);
	bool SendEvent(const std::string& elementAddress, const std::string& type, const std::string& value);
	bool DebuggerOff();
	bool DebuggerOn();
	bool DebuggerToggle();
	bool UnregisterEvent(const std::string& elementAddress, const std::string& type);
	static Rml::Event* addressToEvent(const std::string& address);
	static std::string eventToAddress(Rml::Event* event);
	static Rml::Element* addressToElement(const std::string& address);
	static std::string elementToAddress(Rml::Element* element);
	std::string href;
	std::string protocol;
	std::string _path;
	std::string workingPath;
	Rml::Context* context;
	Rml::ElementDocument* document;
	static RmlFile* rmlMainFile;
	Rml::Element* hover;
	RmlMainConverter rmlMainConverter;
};

#endif //RmlMain_H
