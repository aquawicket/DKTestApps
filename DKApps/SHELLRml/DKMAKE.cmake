DKDEPEND(opengl)
DKDEPEND(agl)
DKDEPEND(xquartz)
DKDEPEND(libx11-dev)
DKDEPEND(shlwapi.lib)
DKDEPEND(zlib)
DKDEPEND(giflib)
DKDEPEND(libpng)
DKDEPEND(libjpeg-turbo)
DKDEPEND(libwebp)
DKDEPEND(tiff)
DKDEPEND(glew)
DKDEPEND(rmlui rmlui_debugger)

# rmlui shell
DKINCLUDE(${RMLUI}/Samples/shell/include)
ADD_SOURCE(${RMLUI}/Samples/shell/include/*.*)
ADD_SOURCE(${RMLUI}/Samples/shell/src/*.*)
IF(WIN)
	ADD_SOURCE(${RMLUI}/Samples/shell/include/win32/*.*)
	ADD_SOURCE(${RMLUI}/Samples/shell/src/win32/*.*)
ENDIF()
IF(MAC OR IOS)
	ADD_SOURCE(${RMLUI}/Samples/shell/include/macosx/*.*)
	ADD_SOURCE(${RMLUI}/Samples/shell/src/macosx/*.*)
ENDIF()
IF(LINUX)
	ADD_SOURCE(${RMLUI}/Samples/shell/include/x11/*.*)
	ADD_SOURCE(${RMLUI}/Samples/shell/src/x11/*.*)
ENDIF()