#include "RmlFile.h"
#include "RmlMain.h"
#include "RmlUtility.h"


RmlFile* RmlFile::Get() {
	return rmlFile;
}

bool RmlFile::pathExists(const std::string path)
{
	//TODO
	return false;
}

bool RmlFile::MakeDir(const std::string path)
{
	//TODO
	return false;
}

bool RmlFile::PathExists(const std::string path)
{
	//TODO
	return false;
}

bool RmlFile::GetFilename(const std::string path, std::string& filename)
{
	//TODO
	return false;
}

bool RmlFile::VerifyPath(std::string& path)
{
	//TODO
	return false;
}

bool RmlFile::FileInterface(const std::filesystem::path& root)
{
	rmlFile = this;
	std::string _root{ root.u8string() };
}

Rml::FileHandle RmlFile::Open(const Rml::String& path)
{
	std::string _path = path;
	//if (has(_path, ":/")) { //could be http:// , https:// or C:/
		//absolute path
	//}
	//else if(has(_path,"//")){ //could be //www.site.com/style.css or //site.com/style.css
		//_path = RmlMain::Get()->protocol+":"+_path;
		//return ERROR("RmlMain::LoadUrl(): no protocol specified\n"); //absolute path without protocol
	//}
	// else{
		if(RmlFile::PathExists(RmlMain::Get()->workingPath+_path))
			_path = RmlMain::Get()->workingPath+_path;
		else if(!RmlFile::VerifyPath(_path)){
			return RMLERROR("could not locate path ("+_path+")");
		}
		//if(_path.find("/home") == std::string::npos) //url may have unix home directory
		//	_path = RmlMain::Get()->workingPath+_path;
		//return ERROR("RmlMain::LoadUrl(): cannot load relative paths\n");
	//}
	if(RmlUtility::stringContains(_path,"://")){
		RmlFile::MakeDir(_root+"/Cache");
		std::string filename;
		RmlFile::GetFilename(_path, filename);
		//remove everything after ? in the filename if there is one
		unsigned long found = filename.rfind("?");
		if(found > 0)
			filename = filename.substr(0,found);
#ifdef USE_Curl
		Curl::Get()->Download(_path, File::local_assets+"Cache/"+filename);
		_path = File::local_assets+"Cache/"+filename;
#endif
	}

	FILE* fp = fopen(_path.c_str(), "rb");
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


bool RmlFile::PathExists(const std::string& path)
{
	//TODO
}
