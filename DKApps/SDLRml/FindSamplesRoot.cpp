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

#ifdef RMLUI_PLATFORM_UNIX
	Rml::String testPath = "";
	char* resolved_path = NULL;
	char buf[PATH_MAX + 1] = {0};
	Rml::String appPath = "";
	
	#ifdef RMLUI_PLATFORM_MACOSX
		uint32_t bufsize = PATH_MAX;
		if(!_NSGetExecutablePath(buf, &bufsize))
			puts(buf);
		appPath = Rml::String(buf);
	#endif
	#ifdef RMLUI_PLATFORM_LINUX
		realpath("/proc/self/exe", buf);
		appPath = Rml::String(buf);
	#endif
	printf("appPath = %s\n", appPath.c_str());
	
	testPath = appPath+"/Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	
	testPath = appPath+"/../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	printf("resolved_path = %s\n", resolved_path.c_str());
	
	testPath = appPath+"/../../../../../../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../../../../../Samples";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	
	testPath = appPath+"/assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }
	testPath = appPath+"/../../../../../../../assets";
	if(!resolved_path){ resolved_path = realpath(testPath.c_str(), NULL); }

    if(!resolved_path){
        printf("ERROR: could not locate assets path \n");
		return "";
	}
    Rml::String out(resolved_path);
#endif


	printf("out = %s\n", out.c_str());
	return out+"/";
}
