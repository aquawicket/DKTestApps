#include <RmlUi/Core.h>
#include "Shell.h"
#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#else
    #include <sys/stat.h>
#endif
    

Rml::String Shell::FindSamplesRoot() 
{
	Rml::String path = "";
	
#ifdef RMLUI_PLATFORM_WIN32
	if(path.empty() && PathFileExistsA("../Samples"))
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
    struct stat buffer;
    if(path.empty() && (stat ("../Samples", &buffer) == 0) )
        path = "../Samples";
    if(path.empty() && (stat ("../../Samples", &buffer) == 0) )
        path = "../../Samples";
    if(path.empty() && (stat ("../../../Samples", &buffer) == 0) )
        path = "../../../Samples";
    if(path.empty() && (stat ("../../../../Samples", &buffer) == 0) )
        path = "../../../../Samples";
    if(path.empty() && (stat ("../../../../../Samples", &buffer) == 0) )
        path = "../../../../../Samples";
    if(path.empty() && (stat ("../../../../../../Samples", &buffer) == 0) )
        path = "../../../../../../Samples";
    if (path.empty() && (stat ("../assets", &buffer) == 0) )
        path = "../assets";
    if (path.empty() && (stat ("../../assets", &buffer) == 0) )
        path = "../../assets";
	char *resolved_path = realpath(path.c_str(), NULL);
    if(!resolved_path)
        return "";
    Rml::String out(resolved_path);
#endif
	return out;
}
