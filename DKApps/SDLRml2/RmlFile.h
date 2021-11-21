#pragma once
#ifndef RmlFile_H
#define RmlFile_H
#include <RmlUi/Core.h>
#include <filesystem>

class RmlFile : public Rml::FileInterface 
{
public:
	static RmlFile* Get();
	static bool pathExists(const std::string path);
	static bool MakeDir(const std::string path);
	static bool PathExists(const std::string path);
	static bool GetFilename(const std::string path, std::string& filename);
	static bool VerifyPath(std::string& path);
	static bool FileToString(const std::string file, std::string& str);

	bool FileInterface(const std::filesystem::path& root);
	virtual Rml::FileHandle Open(const Rml::String& path);
	virtual void Close(Rml::FileHandle file);
	virtual size_t Read(void* buffer, size_t size, Rml::FileHandle file);
	virtual bool Seek(Rml::FileHandle file, long offset, int origin);
	virtual size_t Tell(Rml::FileHandle file);
	bool PathExists(const std::string& path);
	static RmlFile* rmlFile;
	std::string _root;

};

#endif //RmlFile_H
