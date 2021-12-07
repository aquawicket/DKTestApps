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
DKCOPY(${RMLUI}/Samples/basic/sdl2/src/ ${DKPROJECT}/ FALSE)
DKCOPY(${RMLUI}/Samples/shell/include/Shell.h ${DKPROJECT}/Shell.h FALSE)
DKCOPY(${RMLUI}/Samples/shell/src/Shell.cpp ${DKPROJECT}/Shell.cpp FALSE)
DKCOPY(${RMLUI}/Samples/shell/include/ShellFileInterface.h ${DKPROJECT}/ShellFileInterface.h FALSE)
DKCOPY(${RMLUI}/Samples/shell/src/ShellFileInterface.cpp ${DKPROJECT}/ShellFileInterface.cpp FALSE)
DKCOPY(${RMLUI}/Samples/shell/include/ShellRenderInterfaceExtensions.h ${DKPROJECT}/ShellRenderInterfaceExtensions.h FALSE)
DKCOPY(${RMLUI}/Samples/shell/include/ShellSystemInterface.h ${DKPROJECT}/ShellSystemInterface.h FALSE)

# rmlui shell
#DKINCLUDE(${RMLUI}/Samples/shell/include)
#ADD_SOURCE(${RMLUI}/Samples/shell/include/*.*)
#ADD_SOURCE(${RMLUI}/Samples/shell/src/*.*)

# rmlui unused shell when using sdl2
#REMOVE_SOURCE(Input.*)
#REMOVE_SOURCE(precompiled.*)
#REMOVE_SOURCE(ShellOpenGL.*)
#REMOVE_SOURCE(ShellRenderInterfaceOpenGL.*)
#REMOVE_SOURCE(ShellRenderInterfaceExtensions.*)
#REMOVE_SOURCE(ShellSystemInterface.*)

# rmlui sdl2
#DKINCLUDE(${RMLUI}/Samples/basic/sdl2/src)
#ADD_SOURCE(${RMLUI}/Samples/basic/sdl2/src/RenderInterfaceSDL2.*)
#ADD_SOURCE(${RMLUI}/Samples/basic/sdl2/src/SystemInterfaceSDL2.*)
#ADD_SOURCE(${RMLUI}/Samples/basic/sdl2/src/main.cpp)