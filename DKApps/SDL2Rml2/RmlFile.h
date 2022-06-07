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
