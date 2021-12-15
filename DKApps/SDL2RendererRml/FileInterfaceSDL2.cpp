#include "FileInterfaceSDL2.h"


RmlUiSDL2FileInterface::RmlUiSDL2FileInterface(const Rml::String& root) : root(root)
{
}

RmlUiSDL2FileInterface::~RmlUiSDL2FileInterface()
{
}

/// Opens a file for use with RmlUi
/// @param file The file handle to Open().
Rml::FileHandle RmlUiSDL2FileInterface::Open(const Rml::String& path)
{
	FILE* fp = fopen(path.c_str(), "rb");
	return (Rml::FileHandle) fp;
}

/// Closes a previously opened file.
/// @param file The file handle previously opened through Open().
void RmlUiSDL2FileInterface::Close(Rml::FileHandle file)
{
	fclose((FILE*) file);
}

/// Reads data from a previously opened file.
/// @param buffer The buffer to be read into.
/// @param size The number of bytes to read into the buffer.
/// @param file The handle of the file.
/// @return The total number of bytes read into the buffer.
size_t RmlUiSDL2FileInterface::Read(void* buffer, size_t size, Rml::FileHandle file)
{
	return fread(buffer, 1, size, (FILE*) file);
}

/// Seeks to a point in a previously opened file.
/// @param file The handle of the file to seek.
/// @param offset The number of bytes to seek.
/// @param origin One of either SEEK_SET (seek from the beginning of the file), SEEK_END (seek from the end of the file) or SEEK_CUR (seek from the current file position).
/// @return True if the operation completed successfully, false otherwise.
bool RmlUiSDL2FileInterface::Seek(Rml::FileHandle file, long offset, int origin)
{
	return fseek((FILE*) file, offset, origin) == 0;
}

/// Returns the current position of the file pointer.
/// @param file The handle of the file to be queried.
/// @return The number of bytes from the origin of the file.
size_t RmlUiSDL2FileInterface::Tell(Rml::FileHandle file)
{
	return ftell((FILE*) file);
}
