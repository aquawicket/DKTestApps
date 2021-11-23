#include <RmlUi/Core.h>
#include <RmlUi/Core/StringUtilities.h>
#include "Shell.h"

#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#endif
#ifdef RMLUI_PLATFORM_MACOSX
	#include <mach-o/dyld.h>
	#include <limits.h>
#endif
#ifdef RMLUI_PLATFORM_LINUX
	#include <libgen.h>         // dirname
	#include <unistd.h>         // readlink
	#include <linux/limits.h>   // PATH_MAX
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
		GetModuleFileName( NULL, buffer, MAX_PATH );
		appPath = Rml::String(buffer);
	#endif
	
	#ifdef RMLUI_PLATFORM_MACOSX
		char buf[PATH_MAX + 1] = {0};
		uint32_t bufsize = PATH_MAX;
		if(!_NSGetExecutablePath(buf, &bufsize))
			puts(buf);
		appPath = Rml::String(buf);
	#endif
	
	#ifdef RMLUI_PLATFORM_LINUX
		char buf[PATH_MAX + 1] = {0};
		if(!realpath("/proc/self/exe", buf))
			printf("ERROR: could not get appPath from /proc/self/exe \n");
		appPath = Rml::String(buf);
	#endif
	printf("appPath = %s\n", appPath.c_str());

	Rml::String testPath = appPath +"/";
	testPath = Rml::StringUtilities::Replace(testPath, '\\', '/');
	
	for (unsigned int i = 0; i < 15; i++) {
		Rml::String doPath = testPath + "Samples/";
		printf("doPath = %s\n", doPath.c_str());

		#ifdef RMLUI_PLATFORM_WIN32
		char resolved_path[256];
			char* fileExt;
			if (PathFileExistsA(doPath.c_str())) {
				doPath = Rml::StringUtilities::Replace(doPath, "\\", "/");
				GetFullPathName(doPath.c_str(), 256, resolved_path, &fileExt);
				printf("resolved_path = %s\n", doPath.c_str());
				return doPath+"/";
			}
			else{
				testPath = testPath + "../";
				continue;
			}
		#endif
		#ifdef RMLUI_PLATFORM_MACOSX
			char* resolved_path = NULL;
			struct stat info;
			if (stat(doPath.c_str(), &info) != 0) {
				resolved_path = realpath(doPath.c_str(), NULL);
				if (resolved_path) {
					printf("resolved_path = %s\n", resolved_path);
					return Rml::String(resolved_path) + "/";
				}
			}
			testPath = testPath + "../";
		#endif
		#ifdef RMLUI_PLATFORM_LINUX
			char* resolved_path = NULL;
			resolved_path = realpath(testPath.c_str(), buf);
			if (resolved_path) {
				printf("resolved_path = %s\n", resolved_path);
				return Rml::String(resolved_path);
			}
			testPath = testPath + "../";
		#endif
	}
	
	printf("ERROR: could not locate assets path \n");
	return "";
}
