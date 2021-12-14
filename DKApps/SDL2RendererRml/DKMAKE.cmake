DKDEPEND(opengl)
#DKDEPEND(agl)
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
DKDEPEND(sdl2)
DKDEPEND(sdl2_image)
DKDEPEND(rmlui)


# import rmlui sdl2 sample source
#DKCOPY(${RMLUI}/Samples/basic/sdl2/src/ ${DKPROJECT}/ FALSE)
#DKCOPY(${RMLUI}/Samples/shell/include/Shell.h ${DKPROJECT}/Shell.h FALSE)
#DKCOPY(${RMLUI}/Samples/shell/src/Shell.cpp ${DKPROJECT}/Shell.cpp FALSE)
#DKCOPY(${RMLUI}/Samples/shell/include/ShellFileInterface.h ${DKPROJECT}/ShellFileInterface.h FALSE)
#DKCOPY(${RMLUI}/Samples/shell/src/ShellFileInterface.cpp ${DKPROJECT}/ShellFileInterface.cpp FALSE)
#DKCOPY(${RMLUI}/Samples/shell/include/ShellRenderInterfaceExtensions.h ${DKPROJECT}/ShellRenderInterfaceExtensions.h FALSE)
#DKCOPY(${RMLUI}/Samples/shell/include/ShellSystemInterface.h ${DKPROJECT}/ShellSystemInterface.h FALSE)

DKINCLUDE(${RMLUI}/Samples/shell/include)

# rmlui shell
DKINCLUDE(${RMLUI}/Samples/basic/sdl2_sdlrenderer/src)
ADD_SOURCE(${RMLUI}/Samples/basic/sdl2_sdlrenderer/src/*)

#Samples/basic/sdl2_sdlrenderer/src/RenderInterfaceSDL2.cpp
#Samples/basic/sdl2_sdlrenderer/src/RenderInterfaceSDL2.h
#Samples/basic/sdl2_sdlrenderer/src/SystemInterfaceSDL2.cpp
#amples/basic/sdl2_sdlrenderer/src/SystemInterfaceSDL2.h
#Samples/basic/sdl2_sdlrenderer/src/main.cpp