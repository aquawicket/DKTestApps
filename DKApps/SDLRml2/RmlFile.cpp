#include "RmlFile.h"
#include "Rml.h"
//#include "DKCurl/DKCurl.h"

Rml::FileHandle RmlFile::Open(const Rml::String& path){

	DKString _url = path;
	
	if (has(_url, ":/")) { //could be http:// , https:// or C:/
		//absolute path
	}
	else if(has(_url,"//")){ //could be //www.site.com/style.css or //site.com/style.css
		//_url = RmlMain::Get()->protocol+":"+_url;
		return DKERROR("RmlMain::LoadUrl(): no protocol specified\n"); //absolute path without protocol
	}
	else{
		if(DKFile::PathExists(RmlMain::Get()->workingPath+_url))
			_url = RmlMain::Get()->workingPath+_url;
		else if(!DKFile::VerifyPath(_url)){
			return DKERROR("could not locate path ("+_url+")");
		}
		//if(_url.find("/home") == std::string::npos) //url may have unix home directory
		//	_url = RmlMain::Get()->workingPath+_url;
		//return DKERROR("RmlMain::LoadUrl(): cannot load relative paths\n");
	}
	if(has(_url,"://")){
		DKFile::MakeDir(DKFile::local_assets+"Cache");
		DKString filename;
		DKFile::GetFileName(_url, filename);
		//remove everything after ? in the filename if there is one
		unsigned long found = filename.rfind("?");
		if(found > 0)
			filename = filename.substr(0,found);
#ifdef USE_DKCurl
		DKCurl::Get()->Download(_url, DKFile::local_assets+"Cache/"+filename);
		_url = DKFile::local_assets+"Cache/"+filename;
#endif
	}

	FILE* fp = fopen(_url.c_str(), "rb");
	return (Rml::FileHandle) fp;
}

/// Closes a previously opened file.
/// @param file The file handle previously opened through Open().
void RmlFile::Close(Rml::FileHandle file){
	fclose((FILE*) file);
}

/// Reads data from a previously opened file.
/// @param buffer The buffer to be read into.
/// @param size The number of bytes to read into the buffer.
/// @param file The handle of the file.
/// @return The total number of bytes read into the buffer.
size_t RmlFile::Read(void* buffer, size_t size, Rml::FileHandle file){
	return fread(buffer, 1, size, (FILE*) file);
}

/// Seeks to a point in a previously opened file.
/// @param file The handle of the file to seek.
/// @param offset The number of bytes to seek.
/// @param origin One of either SEEK_SET (seek from the beginning of the file), SEEK_END (seek from the end of the file) or SEEK_CUR (seek from the current file position).
/// @return True if the operation completed successfully, false otherwise.
bool RmlFile::Seek(Rml::FileHandle file, long offset, int origin){
	return fseek((FILE*) file, offset, origin) == 0;
}

/// Returns the current position of the file pointer.
/// @param file The handle of the file to be queried.
/// @return The number of bytes from the origin of the file.
size_t RmlFile::Tell(Rml::FileHandle file){
	return ftell((FILE*) file);
}
