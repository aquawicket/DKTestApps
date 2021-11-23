#include <RmlUi/Core.h>
#include <RmlUi/Core/StringUtilities.h> //Rml::StringUtilities::Replace
#include "Shell.h"

#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <clocale>

#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"            // GetModuleFileName
#endif
#ifdef RMLUI_PLATFORM_MACOSX
	#include <mach-o/dyld.h>      // _NSGetExecutablePath
	#include <limits.h>			// PATH_MAX
	//#include <sys/stat.h>         // directory
#endif
#ifdef RMLUI_PLATFORM_LINUX
	//#include <libgen.h>           // dirname
	#include <unistd.h>           // chdir, readlink
	#include <linux/limits.h>     // PATH_MAX
	#include <sys/stat.h>          // S_ISDIR
#endif

#ifndef __has_include
	static_assert(false, "__has_include not supported");
#else
	#if /*__cplusplus >= 201703L &&*/ __has_include(<filesystem>)
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

Rml::String Shell::FindSamplesRoot()
{
	Rml::String path = "";
#ifdef WIN32
	path = "";
#else
	path = "";
#endif	

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

	printf("appPath = %s\n", appPath.c_str());
	printf("current_path = %s\n", fs::current_path().string().c_str());
	appPath = fs::current_path().string();

	Rml::String basePath = appPath + "/";
	basePath = Rml::StringUtilities::Replace(basePath, '\\', '/');

	for (unsigned int i = 0; i < 15; i++) {
		Rml::String tryPath = basePath + "Samples/";
		printf("tryPath = %s\n", tryPath.c_str());

#	ifdef RMLUI_PLATFORM_WIN32
		Rml::String realPath;
		char full[_MAX_PATH];
		if (_fullpath(full, tryPath.c_str(), _MAX_PATH) != NULL) {
			printf("Full path is: %s\n", full);
			Rml::String realPath = Rml::String(full);
			realPath = Rml::StringUtilities::Replace(realPath, '\\', '/');
			printf("realPath is: %s\n", realPath.c_str());
			if (fs::exists(realPath)) {
				printf("	PATH FOUND\n");
				fs::current_path(realPath);
				return realPath;
			}
		}
		printf("  not found\n");
		basePath = basePath + "../";
		continue;
#	endif // RMLUI_PLATFORM_WIN32

#	ifdef RMLUI_PLATFORM_MACOSX
		char* realPath = realpath(tryPath.c_str(), NULL);
		if (realPath) {
			printf("realPath is: %s\n", realPath);
			if (fs::exists(realPath)) {
				printf("	PATH FOUND\n");
				fs::current_path(realPath);
				return (Rml::String(realPath)+"/");
			}
		}
		printf("  not found\n");
		basePath = basePath + "../";
		continue;
#	endif // RMLUI_PLATFORM_MACOSX

#	ifdef RMLUI_PLATFORM_LINUX
	

		Rml::StringUtilities::Replace(tryPath, fs::current_path().string(), "");
		char* fullPath = (char*)malloc(PATH_MAX);
		if (::realpath(tryPath.c_str(), fullPath) != NULL) {
			printf("fullPath is: %s\n", fullPath);
			Rml::String realPath = Rml::String(fullPath);
			//if (realPath) {
				printf("realPath is: %s\n", realPath);
				if (fs::exists(realPath)) {
					printf("	PATH FOUND\n");
					fs::current_path(realPath);
					return Rml::String(realPath);
				}
			//}
		}
		else {
			if (errno)
				std::cout << "ERROR: realpath():  " << std::strerror(errno) << '\n';
		}
		printf("  not found\n");
		basePath = basePath + "../";
		continue;
#	endif // RMLUI_PLATFORM_LINUX

	}

	printf("ERROR: could not locate assets path \n");
	return "";
}
