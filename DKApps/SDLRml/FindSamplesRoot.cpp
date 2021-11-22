#include <RmlUi/Core.h>
#include "Shell.h"
#ifdef RMLUI_PLATFORM_WIN32
	#include "Shlwapi.h"
#else
    #include <sys/stat.h>
    #include <unistd.h>
#endif
    

Rml::String Shell::FindSamplesRoot() 
{
    Rml::String path = "/Users/aquamac/digitalknob/DKTestApps/DKApps/SDLRml";
    struct stat buffer;
    if(stat ("/../../Samples/", &buffer) != 0){
        printf("%s DOES NOT EXIST\n", path.c_str());
        path = "";
    }
    else{
        printf("********** PATH EXISTS **********");
    }
    char *buf;
    buf=(char *)malloc(100*sizeof(char));
    getcwd(buf,100);
    printf("\n %s \n",buf);
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
    
    if(path.empty() && (stat ("/../Samples/", &buffer) == 0) )
        path = "/../Samples/";
    if(path.empty() && (stat ("/../../Samples/", &buffer) == 0) )
        path = "/../../Samples/";
    if(path.empty() && (stat ("/../../../Samples/", &buffer) == 0) )
        path = "/../../../Samples/";
    if(path.empty() && (stat ("../../../../Samples/", &buffer) == 0) )
        path = "../../../../Samples/";
    if(path.empty() && (stat ("../../../../../Samples/", &buffer) == 0) )
        path = "../../../../../Samples/";
    if(path.empty() && (stat ("../../../../../../Samples/", &buffer) == 0) )
        path = "../../../../../../Samples/";
    if(path.empty() && (stat ("../../../../../../../Samples/", &buffer) == 0) )
        path = "../../../../../../../Samples/";
    if(path.empty() && (stat ("../../../../../../../../Samples/", &buffer) == 0) )
        path = "../../../../../../../../Samples/";
    if (path.empty() && (stat ("/../assets", &buffer) == 0) )
        path = "/../assets";
    if (path.empty() && (stat ("/../../assets", &buffer) == 0) )
        path = "/../../assets";
	char *resolved_path = realpath(path.c_str(), NULL);
    if(!resolved_path)
        return "";
    Rml::String out(resolved_path);
#endif
	return out;
}
