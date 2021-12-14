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

# rmlui shell
DKINCLUDE(${RMLUI}/Samples/basic/sdl2_sdlrenderer/src)
ADD_SOURCE(${RMLUI}/Samples/basic/sdl2_sdlrenderer/src/*)

#Samples/basic/sdl2_sdlrenderer/src/RenderInterfaceSDL2.cpp
#Samples/basic/sdl2_sdlrenderer/src/RenderInterfaceSDL2.h
#Samples/basic/sdl2_sdlrenderer/src/SystemInterfaceSDL2.cpp
#amples/basic/sdl2_sdlrenderer/src/SystemInterfaceSDL2.h
#Samples/basic/sdl2_sdlrenderer/src/main.cpp