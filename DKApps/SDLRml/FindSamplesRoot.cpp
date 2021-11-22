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
    path = "";//Users/aquamac/digitalknob/DKTestApps/DKApps/SDLRml/Samples";
    
#endif
#ifdef RMLUI_PLATFORM_WIN32
	if(path.empty() && PathFileExistsA("/../Samples"))
		path = "../Samples";
	if(path.empty() && PathFileExistsA("../../Samples"))
		path = "../../Samples";
	if (path.empty() && PathFileExistsA("../assets"))
		path = "../assets";
	if (path.empty() && PathFileExistsA("../../assets"))
		path = "../../assets";
	char *fileExt;
	char resolved_path[256];
	GetFullPathName(path.c_str(), 256, resolved_path, &fileExt);
	Rml::String out(resolved_path);
#else
	char buf [PATH_MAX];
	uint32_t bufsize = PATH_MAX;
	if(!_NSGetExecutablePath(buf, &bufsize))
    puts(buf);
	Rml::String appPath(buf);
    
    struct stat buffer = {};
    if(!path.empty() && stat (path.c_str(), &buffer) != 0){
        path = "PATH IS INVALID\n";
        printf("--> %s", path.c_str());
    }
	
	Rml::String testPath = "";
	testPath = appPath+"/Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
 
	testPath = appPath+"/../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(testPath))
        path = testPath;



	testPath = appPath+"/../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(appPath+"/../../../../../DKMAKE.cmake"))
        path = testPath;
	
	testPath = appPath+"/../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(appPath+"/../../../../../../DKMAKE.cmake"))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(appPath+"/../../../../../../../DKMAKE.cmake"))
        path = testPath;
	
	testPath = appPath+"/../../../../../../../../Samples";
	printf("testPath = %s\n", testPath.c_str());
	//buffer = {};
    //if(path.empty() && (stat ((testPath.c_str()), &buffer) == 0) )
    if(std::filesystem::exists(appPath+"/../../../../../../../../DKMAKE.cmake"))
        path = testPath;
	
	char *resolved_path = realpath(path.c_str(), NULL);
    if(!resolved_path)
        return "";
    Rml::String out(resolved_path);
#endif
	return out+"/";
}
