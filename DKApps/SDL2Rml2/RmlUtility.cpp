#include "RmlUtility.h"

bool RmlUtility::stringContains(const Rml::String& str, const Rml::String& has)
{
	//TODO
	return false;
}

bool RmlUtility::replace(Rml::String& str, const Rml::String& with, const Rml::String& newstr)
{
	//TODO
	return false;
}

bool RmlUtility::stringsMatch(const Rml::String& strA, const Rml::String& strB)
{
	//TODO
	return false;
}

void RmlUtility::Sleep(unsigned int milliseconds)
{
	//TODO
	return;
}

bool RmlUtility::Log(const char* file, int line, const char* func, const Rml::String& message, const int lvl) {
	printf("%s: %d: %s, %s, %d", file, line, func, message.c_str(), lvl);
	if (lvl == LOGERROR)
		return false;
	return true;
}