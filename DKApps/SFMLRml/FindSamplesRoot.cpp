#include <RmlUi/Core.h>
#include "Shell.h"
#include <filesystem>
#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#else
    #include <sys/stat.h>
    #include <unistd.h>
	#include <mach-o/dyld.h>
	#include <limits.h>
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
#else
	Rml::String testPath = "";
	char* resolved_path = "";
	char buf [PATH_MAX];
	uint32_t bufsize = PATH_MAX;
	if(!_NSGetExecutablePath(buf, &bufsize))
    puts(buf);
	Rml::String appPath(buf);
	
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
	testPath = appPath+"/../../../../../../../../assets";

    if(!resolved_path){
		printf()
        return "ERROR: could not locate assets path";
	}
    Rml::String out(resolved_path);
#endif
	printf("out = %s\n", out.c_str());
	return out+"/";
}
