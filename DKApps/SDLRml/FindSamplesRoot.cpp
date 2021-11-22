#include <RmlUi/Core.h>
#include "Shell.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

Rml::String Shell::FindSamplesRoot() 
{
	Rml::String path = "";
	
#ifdef WIN32
	if(PathFileExistsA("../Samples")
		path = "../Samples";
	if(PathFileExistsA("../../Samples")
		path = "../../Samples";
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
