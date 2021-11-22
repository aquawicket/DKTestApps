DKDEPEND(opengl)
DKDEPEND(agl)
#DKDEPEND(xquartz)
DKDEPEND(libx11-dev)
DKDEPEND(shlwapi.lib)
DKDEPEND(zlib)
DKDEPEND(giflib)
DKDEPEND(libpng)
DKDEPEND(libjpeg-turbo)
DKDEPEND(libwebp)
DKDEPEND(tiff)
DKDEPEND(glew)
#DKDEPEND(sdl2)
#DKDEPEND(sdl2_image)
DKDEPEND(rmlui rmlui_debugger)

DKINCLUDE(${RMLUI}/Samples/shell/include)
DKSET(SRC_INCLUDE ${RMLUI}/Samples/shell/*)
DKSET(SRC_EXCLUDE
	App.h
	App.cpp
	InputMacOSX.* 
	InputX11.*
	X11MacroZapper.*
	ShellRenderInterfaceExtensionsOpenGL_X11.*
	ShellX11.*
	ShellMacOSX.*
	ShellRenderInterfaceExtensionsOpenGL_MacOSX.*)