// This will allow you to print out the predefined macros in Microsoft Visual C++
// To print C predefiend macros:    cl.exe /B1VCMacros.exe macros.c  
// To print C++ predefiend macros:  cl.exe /BxVCMacros.exe macros.cpp
// Example: 
// C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\bin\Hostx86\x86\cl.exe /BxC:\Users\Administrator\digitalknob\DKTestApps\DKApps\VCMacros\win32\Release\VCMacros.exe macros.cpp
// https://stackoverflow.com/a/3672331/688352

// The Microsoft C/C++ compiler allows an alternative compiler front-end to be invoked using the /B1 and /Bx 
// command line switches for .c and .cpp files respectively. The command-line interface module CL.exe passes 
// a list of options to the replacement compiler front-end via the MSC_CMD_FLAGS environment variable. 
// This list of options includes -D macro definitions for some of the predefined macros.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char* p;

    if ((p = getenv("MSC_CMD_FLAGS")) != NULL)
        printf("MSC_CMD_FLAGS:n%sn", p);

    if ((p = getenv("MSC_IDE_FLAGS")) != NULL)
        printf("MSC_IDE_FLAGS:n%sn", p);

    return EXIT_FAILURE;
}