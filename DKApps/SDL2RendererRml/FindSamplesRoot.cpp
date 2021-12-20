/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 Nuno Silva
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "FileInterfaceSDL2.h"
#include <RmlUi/Core/StringUtilities.h>  //Rml::StringUtilities::Replace
#include <iostream>

#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"      // GetModuleFileName
	#include <direct.h>       // chdir
#endif
#ifdef RMLUI_PLATFORM_MACOSX
	#include <mach-o/dyld.h>  // _NSGetExecutablePath
	#include <limits.h>	      //  PATH_MAX
	#include "unistd.h"
#endif
#ifdef RMLUI_PLATFORM_LINUX
	#include <linux/limits.h> // PATH_MAX
	#include "unistd.h"
#endif
#include <sys/stat.h>

Rml::String FileInterfaceSDL2::FindSamplesRoot()
{
	Rml::String path = "";
	Rml::String appPath = "";

#ifdef RMLUI_PLATFORM_WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	appPath = Rml::String(buffer);
#endif

#ifdef RMLUI_PLATFORM_MACOSX
	char buf[PATH_MAX + 1] = { 0 };
	uint32_t bufsize = PATH_MAX;
	if (!_NSGetExecutablePath(buf, &bufsize))
		puts(buf);
	appPath = Rml::String(buf);
#endif

#ifdef RMLUI_PLATFORM_LINUX
	char buf[PATH_MAX + 1] = { 0 };
	if (!realpath("/proc/self/exe", buf))
		printf("ERROR: could not get appPath from /proc/self/exe \n");
	appPath = Rml::String(buf);
#endif

	printf("appPath = %s \n", appPath.c_str());
	std::size_t found = appPath.find_last_of("/");
	appPath = appPath.substr(0,found); //point the path to the app folder by removing the executbale from the end
	
	Rml::String basePath = appPath + "/";
	basePath = Rml::StringUtilities::Replace(basePath, '\\', '/'); //normalize windows backslashes 

	for (unsigned int i = 0; i < 15; i++) { //Start at the top and go back N levels in search of our assets location
		Rml::String tryPath = basePath + "Samples";

#ifdef RMLUI_PLATFORM_WIN32
		Rml::String realPath;
		char full[_MAX_PATH];
		if (_fullpath(full, tryPath.c_str(), _MAX_PATH) != NULL) {
			realPath = Rml::String(full);
			realPath = Rml::StringUtilities::Replace(realPath, '\\', '/');
			struct stat buf;
			if(stat(realPath.c_str(), &buf) == 0){ //does path exist?
				if(_chdir(realPath.c_str()) != 0){
					printf("ERROR: _chdir failed \n");
					return "";
				}
				return realPath;
			}
		}
#endif

#ifdef RMLUI_PLATFORM_MACOSX
		char* realPath = realpath(tryPath.c_str(), NULL);
		if (realPath) {
			struct stat buf;
			if(stat(realPath, &buf) == 0){ //does path exist?
				if( chdir(realPath) != 0){
					printf("ERROR: chdir failed \n");
					return "";
				}
				return (Rml::String(realPath)+"/");
			}
		}
#endif

#ifdef RMLUI_PLATFORM_LINUX
		char* fullPath = (char*)malloc(PATH_MAX);
		if (realpath(tryPath.c_str(), fullPath) != NULL) {
			Rml::String realPath = Rml::String(fullPath);
			struct stat buf;
			if(stat(realPath.c_str(), &buf) == 0){ //does path exist?
				if( chdir(realPath.c_str()) != 0){
					printf("ERROR: chdir failed \n");
					return "";
				}
				return Rml::String(realPath);
			}
		}
		else {
			if (errno)
				std::cout << "ERROR: realpath():  " << std::strerror(errno) << '\n';
		}
#endif
		basePath = basePath + "../";
		continue;
	}
	printf("ERROR: could not locate assets path \n");
	return "";
}
