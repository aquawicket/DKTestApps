#include <RmlUi/Core.h>
#include "Shell.h"
#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#endif

Rml::String Shell::FindSamplesRoot() 
{
	Rml::String path = "";
	
#ifdef RMLUI_PLATFORM_WIN32
#include "Shlwapi.h"
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
	char *resolved_path;
	resolved_path = realpath(path.c_str(), NULL);
	Rml::String out = resolved_path;
#endif
	return out+"/";
}
