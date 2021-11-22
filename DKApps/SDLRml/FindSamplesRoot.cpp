#include <RmlUi/Core.h>
#include "Shell.h"
#include <filesystem>
#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#else
    #include <sys/stat.h>
    #include <unistd.h>
#endif
    

Rml::String Shell::FindSamplesRoot() 
{
    Rml::String path = "";
#ifdef WIN32
    path = "";
#else
    path = "Users/aquamac/digitalknob/DKTestApps/DKApps/SDLRml/Samples";
    
#endif
#ifdef RMLUI_PLATFORM_WIN32
	if(path.empty() && PathFileExistsA("/../Samples"))
		path = ../Samples";
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
    char *buf;
    buf=(char *)malloc(100*sizeof(char));
    getcwd(buf,100);
    printf("\n %s \n",buf);
    Rml::String buff(buf);
    
    struct stat buffer = {};
    if(!path.empty() && stat (path.c_str(), &buffer) != 0){
        path = "PATH IS INVALID\n";
        printf("--> %s", path.c_str());
    }
    //buffer = {};
    //if(path.empty() && (stat (("/../Samples"), &buffer) == 0) )
    if(std::filesystem::exists("../Samples"))
        path = "../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("/../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../Samples"))
        path = "/../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("/../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../Samples"))
        path = "/../../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("../../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../../Samples"))
        path = "../../../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("../../../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../../../Samples"))
        path = "../../../../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("../../../../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../../../../Samples"))
        path = "../../../../../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("../../../../../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../../../../../Samples"))
        path = "../../../../../../../Samples";
    //buffer = {};
    //if(path.empty() && (stat ("../../../../../../../../Samples", &buffer) == 0) )
    if(std::filesystem::exists("../../../../../../../../Samples"))
        path = "../../../../../../../../Samples";
    //buffer = {};
    //if (path.empty() && (stat ("/../assets", &buffer) == 0) )
    if(std::filesystem::exists("../assets"))
        path = "/../assets";
    //buffer = {};
    //if (path.empty() && (stat ("/../../assets", &buffer) == 0) )
    if(std::filesystem::exists("../../assets"))
        path = "/../../assets";
    //buffer = {};
	char *resolved_path = realpath(path.c_str(), NULL);
    if(!resolved_path)
        return "";
    Rml::String out(resolved_path);
#endif
	return out+"/";
}
