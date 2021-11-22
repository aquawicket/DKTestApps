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
	return Rml::String(resolved_path);
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
		if(!realpath("/proc/self/exe", buf)){
			printf("ERROR: could not get appPath from /proc/self/exe \n");
			appPath = Rml::String(buf);
		}
	#endif
	printf("appPath = %s\n", appPath.c_str());
	
	char real_buf[PATH_MAX + 1] = {0};
	testPath = appPath+"/Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	
	testPath = appPath+"/../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	printf("resolved_path = %s\n", resolved_path);
	
	testPath = appPath+"/../../../../../../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../../../../../Samples";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	
	testPath = appPath+"/assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }
	testPath = appPath+"/../../../../../../../assets";
	//real_buf = {0};
	if(realpath(testPath.c_str(), real_buf)) { return Rml::String(real_buf); }

    if(!real_buf){
        printf("ERROR: could not locate assets path \n");
		return "";
	}
    //Rml::String out(real_buf);
#endif


	//printf("out = %s\n", out.c_str());
	//return out+"/";
}
