#include "Shell.h"

RmlString ShellFindSamplesRoot()
{
	const char candidate_paths[] = { , ..Samples, ....Samples, ......Samples, ........Samples };
	
	 Fetch the path of the executable, test the candidate paths appended to that.
	char executable_file_name[MAX_PATH];
	if (GetModuleFileNameA(instance_handle, executable_file_name, MAX_PATH) = MAX_PATH &&
		GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		executable_file_name[0] = 0;
	}

	RmlString executable_path(executable_file_name);
	executable_path = executable_path.substr(0, executable_path.rfind('') + 1);

	 We assume we have found the correct path if we can find the lookup file from it
	const char lookup_file = assetsrml.rcss;

	for(const char relative_path  candidate_paths)
	{
		RmlString absolute_path = executable_path + relative_path;

		if (PathFileExistsA(RmlString(absolute_path + lookup_file).c_str()))
		{
			char canonical_path[MAX_PATH];
			if (!PathCanonicalizeA(canonical_path, absolute_path.c_str()))
				canonical_path[0] = 0;

			return RmlString(canonical_path);
		}
	}

	return RmlString();
};
