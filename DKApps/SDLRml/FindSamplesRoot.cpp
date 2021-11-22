#include <RmlUi/Core.h>
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


#ifdef RMLUI_PLATFORM_WIN32
	if(path.empty() && PathFileExistsA("../Samples"))
		path = "../Samples";
	if(path.empty() && PathFileExistsA("../../Samples"))
		path = "../../Samples";
	if(path.empty() && PathFileExistsA("../../../Samples"))
		path = "../../../Samples";
	if (path.empty() && PathFileExistsA("../assets"))
		path = "../assets";
	if (path.empty() && PathFileExistsA("../../assets"))
		path = "../../assets";
	if (path.empty() && PathFileExistsA("../../../assets"))
		path = "../../../assets";
	char *fileExt;
	char resolved_path[256];
	GetFullPathName(path.c_str(), 256, resolved_path, &fileExt);
	Rml::String out(resolved_path);
#endif


#ifdef RMLUI_PLATFORM_MACOSX
	Rml::String testPath = "";
	char* resolved_path = NULL;
	char buf [PATH_MAX];
	uint32_t bufsize = PATH_MAX;
	if(!_NSGetExecutablePath(buf, &bufsize))
    puts(buf);
	Rml::String appPath(buf);
#endif
#ifdef RMLUI_PLATFORM_LINUX
	Rml::String testPath = "";
	char* resolved_path = NULL;
	char result[PATH_MAX];
	ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
	if (count != -1)
	Rml::String appPath = dirname(result);
#endif
#ifdef 	RMLUI_PLATFORM_UNIX
	testPath = appPath+"/Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../../../../Samples";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	
	testPath = appPath+"/assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);
	testPath = appPath+"/../../../../../../../assets";
	if(!resolved_path) resolved_path = realpath(testPath.c_str(), NULL);

    if(!resolved_path){
        printf("ERROR: could not locate assets path");
		return "";
	}
    Rml::String out(resolved_path);
#endif


	printf("out = %s\n", out.c_str());
	return out+"/";
}
