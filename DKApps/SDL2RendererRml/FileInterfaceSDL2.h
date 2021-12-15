#pragma once
#ifndef FILEINTERFACESDL2_H
#define FILEINTERFACESDL2_H
#include <RmlUi/Core.h>

class RmlUiSDL2FileInterface : public Rml::FileInterface {
public:
	RmlUiSDL2FileInterface(const Rml::String& root);
	~RmlUiSDL2FileInterface();
	virtual Rml::FileHandle Open(const Rml::String& path);
	virtual void Close(Rml::FileHandle file);
	virtual size_t Read(void* buffer, size_t size, Rml::FileHandle file);
	virtual bool Seek(Rml::FileHandle file, long offset, int origin);
	virtual size_t Tell(Rml::FileHandle file);
	Rml::String root;
};
#endif
