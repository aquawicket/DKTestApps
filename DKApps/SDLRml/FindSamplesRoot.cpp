#include <RmlUi/Core.h>
#include <RmlUi/Core/StringUtilities.h>
#include "Shell.h"

#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"        // GetFullPathName
#endif
#ifdef RMLUI_PLATFORM_MACOSX
	#include <mach-o/dyld.h>    // _NSGetExecutablePath
	#include <limits.h>			// PATH_MAX
	#include <sys/stat.h>       // directory
#endif
#ifdef RMLUI_PLATFORM_LINUX
	#include <libgen.h>         // dirname
	#include <unistd.h>         // readlink
	#include <linux/limits.h>   // PATH_MAX
#endif
#include <filesystem>

#define BUFSIZE 4096

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
	printf("appPath = %s\n", appPath.c_str());

	Rml::String testPath = appPath + "/";
	testPath = Rml::StringUtilities::Replace(testPath, '\\', '/');

	for (unsigned int i = 0; i < 15; i++) {
		Rml::String tryPath = testPath + "Samples/";
		printf("tryPath = %s\n", tryPath.c_str());

#ifdef RMLUI_PLATFORM_WIN32
		//if (PathFileExistsA(tryPath.c_str())) {
		if(std::filesystem::exists(tryPath)){
			printf("	PATH FOUND\n");
			tryPath = Rml::StringUtilities::Replace(tryPath, "\\", "/");
			//char realPath[256];
			//TCHAR** lppPart = { NULL };
			//if (GetFullPathName(tryPath.c_str(), BUFSIZE, realPath, lppPart)) {
			std::error_code ec;
			std::string realPath = std::filesystem::absolute(tryPath, ec).u8string();
			if (ec) 
				printf("ERROR: GetFullPathName(): %s\n", ec.message());
			else{
				realPath = Rml::StringUtilities::Replace(realPath, '\\', '/');
				printf("realPath = %s\n", realPath.c_str());
				return realPath + "/";
			}
		}
		else {
			printf("  not found\n");
			testPath = testPath + "../";
			continue;
		}
#endif
#ifdef RMLUI_PLATFORM_MACOSX
		/*
		char* realPath = NULL;
		struct stat info;
		realPath = realpath(tryPath.c_str(), NULL);
		if ((stat(realPath, &info) != 0) && (info.st_mode & S_IFDIR)) {
			printf("  PATH FOUND\n");
			if (realPath) {
				printf("realPath = %s\n", realPath);
				return Rml::String(realPath) + "/";
			}
		}
		else {
			printf("  not found\n");
			testPath = testPath + "../";
		}
		*/
		//if (PathFileExistsA(tryPath.c_str())) {
		if (std::filesystem::exists(tryPath)) {
			printf("	PATH FOUND\n");
			//tryPath = Rml::StringUtilities::Replace(tryPath, "\\", "/");
			//char realPath[256];
			//TCHAR** lppPart = { NULL };
			//if (GetFullPathName(tryPath.c_str(), BUFSIZE, realPath, lppPart)) {
			std::error_code ec;
			std::string realPath = std::filesystem::absolute(tryPath, ec).u8string();
			if (ec)
				printf("ERROR: GetFullPathName(): %s\n", ec.message());
			else {
				realPath = Rml::StringUtilities::Replace(realPath, '\\', '/');
				//printf("realPath = %s\n", realPath.c_str());
				return realPath + "/";
			}
		}
		else {
			printf("  not found\n");
			testPath = testPath + "../";
			continue;
		}
#endif
#ifdef RMLUI_PLATFORM_LINUX
		char* realPath = NULL;
		struct stat info;
		if (stat(tryPath.c_str(), &info) != 0) {
			printf("  PATH FOUND");
			realPath = realpath(tryPath.c_str(), buf);
			if (realPath) {
				printf("realPath = %s\n", realPath);
				return Rml::String(realPath);
			}
		}
		else {
			printf("  not found");
			testPath = testPath + "../";
		}
#endif
	}
	printf("ERROR: could not locate assets path \n");
	return "";
}
