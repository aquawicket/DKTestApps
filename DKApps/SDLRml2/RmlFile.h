#pragma once
#ifndef RmlFile_H
#define RmlFile_H
#include <RmlUi/Core.h>
#include "RmlUtility.h"
#include <filesystem>

class RmlFile : public Rml::FileInterface 
{
public:
	RmlFile(const Rml::String& assets);
	static RmlFile* Get();
	static bool ChDir(const Rml::String& path);
	static bool pathExists(const Rml::String path);
	static bool MakeDir(const Rml::String path);
	static bool PathExists(const Rml::String path);
	static bool GetFilename(const Rml::String path, Rml::String& filename);
	static bool VerifyPath(Rml::String& path);
	static bool FileToString(const Rml::String file, Rml::String& str);
	static bool GetDirectoryContents(const Rml::String& path, Rml::StringList& contents);
	static bool IsDirectory(const Rml::String& path);
	static bool GetExtention(const Rml::String& path, Rml::String& ext);
	static bool GetExeName(Rml::String& path);
	static bool GetExePath(Rml::String& path);
	static bool GetModifiedTime(const Rml::String& file, Rml::String& time);
	static bool RemoveExtention(Rml::String& file);

	//bool FileInterface(const Rml::String& root);
	virtual Rml::FileHandle Open(const Rml::String& path);
	virtual void Close(Rml::FileHandle file);
	virtual size_t Read(void* buffer, size_t size, Rml::FileHandle file);
	virtual bool Seek(Rml::FileHandle file, long offset, int origin);
	virtual size_t Tell(Rml::FileHandle file);
	bool PathExists(const Rml::String& path);
	
	Rml::String _assets;
	static RmlFile* instance;
};

#endif //RmlFile_H
