#include <RmlUi/Core/StringUtilities.h>  //Rml::StringUtilities::Replace
#include "Shell.h"
#include <iostream>

#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"          // GetModuleFileName
#endif
#ifdef RMLUI_PLATFORM_MACOSX
	#include <mach-o/dyld.h>      // _NSGetExecutablePath
	#include <limits.h>			  // PATH_MAX
#endif
#ifdef RMLUI_PLATFORM_LINUX
	#include <linux/limits.h>     // PATH_MAX
#endif

//#define USE_filesystem 1
/*
#ifdef USE_filesystem
#ifndef __has_include
	static_assert(false, "__has_include not supported");
#else
	#if __cplusplus >= 201703L && __has_include(<filesystem>)
		#include <filesystem>
		namespace fs = std::filesystem;
	#elif __has_include(<experimental/filesystem>)
		#include <experimental/filesystem>
		namespace fs = std::experimental::filesystem;
	#elif __has_include(<boost/filesystem.hpp>)
		#include <boost/filesystem.hpp>
		namespace fs = boost::filesystem;
	#else
		static_assert(false, "filesystem unavalable");
	#endif
#endif
#endif
*/

#include <sys/stat.h>
bool pathExists(const std::string& file) {
//#	ifdef USE_filesystem
//		return fs::exists(file);
//#	else
		struct stat buf;
		return (stat(file.c_str(), &buf) == 0);
//#	endif
}

/*
#ifdef _WIN32
	#include <direct.h>
	#define cwd _getcwd
	#define cd _chdir
#else
	#include "unistd.h"
	#define cwd getcwd
	#define cd chdir
#endif
*/



Rml::String Shell::FindSamplesRoot()
{
	Rml::String path = "";
	Rml::String appPath = "";

#ifdef RMLUI_PLATFORM_WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	appPath = Rml::String(buffer);
#endif // RMLUI_PLATFORM_WIN32

#ifdef RMLUI_PLATFORM_MACOSX
	char buf[PATH_MAX + 1] = { 0 };
	uint32_t bufsize = PATH_MAX;
	if (!_NSGetExecutablePath(buf, &bufsize))
		puts(buf);
	appPath = Rml::String(buf);
#endif // RMLUI_PLATFORM_MACOSX

#ifdef RMLUI_PLATFORM_LINUX
	char buf[PATH_MAX + 1] = { 0 };
	if (!realpath("/proc/self/exe", buf))
		printf("ERROR: could not get appPath from /proc/self/exe \n");
	appPath = Rml::String(buf);
#endif // RMLUI_PLATFORM_LINUX

	//printf("current_path = %s\n", fs::current_path().string().c_str()); //we are here
	printf("appPath = %s\n", appPath.c_str());
	std::size_t found = appPath.find_last_of("/");
	appPath = appPath.substr(0,found); //point the path to the app folder by removing the executbale from the end
	
	Rml::String basePath = appPath + "/";
	basePath = Rml::StringUtilities::Replace(basePath, '\\', '/'); //normalize windows backslashes 

	for (unsigned int i = 0; i < 15; i++) { //Start at the top and go back N levels in search of out assets location
		Rml::String tryPath = basePath + "Samples";
		printf("tryPath = %s\n", tryPath.c_str());

#	ifdef RMLUI_PLATFORM_WIN32
		Rml::String realPath;
		char full[_MAX_PATH];
		if (_fullpath(full, tryPath.c_str(), _MAX_PATH) != NULL) {
			printf("Full path is: %s\n", full);
			Rml::String realPath = Rml::String(full);
			realPath = Rml::StringUtilities::Replace(realPath, '\\', '/');
			printf("realPath is: %s\n", realPath.c_str());
			if (pathExists(realPath)) {
				printf("	PATH FOUND\n");
				if(_chdir(realPath.c_str()) != 0){
					printf("ERROR: _chdir failed");
					return "";
				}
				return realPath;
			}
		}
		//basePath = basePath + "../";
		//continue;
#	endif

#	ifdef RMLUI_PLATFORM_MACOSX
		char* realPath = realpath(tryPath.c_str(), NULL);
		if (realPath) {
			printf("realPath is: %s\n", realPath);
			if (pathExists(realPath)) {
				if( chdir(realPath) != 0){
					printf("ERROR: chdir failed");
					return "";
				}
				return (Rml::String(realPath)+"/");
			}
		}
		//basePath = basePath + "../";
		//continue;
#	endif

#	ifdef RMLUI_PLATFORM_LINUX
		char* fullPath = (char*)malloc(PATH_MAX);
		if (realpath(tryPath.c_str(), fullPath) != NULL) {
			printf("fullPath is: %s\n", fullPath);
			Rml::String realPath = Rml::String(fullPath);
			printf("realPath is: %s\n", realPath.c_str());
			if (pathExists(realPath)) {
				if( chdir(realPath.c_str()) != 0){
					printf("ERROR: chdir failed");
					return "";
				}
				return Rml::String(realPath);
			}
		}
		else {
			if (errno)
				std::cout << "ERROR: realpath():  " << std::strerror(errno) << '\n';
		}
#	endif
		basePath = basePath + "../";
		continue;
	}
	printf("ERROR: could not locate assets path \n");
	return "";
}
