DKDEPEND(zlib)
DKDEPEND(giflib)
DKDEPEND(libpng)
DKDEPEND(libjpeg-turbo)
DKDEPEND(libwebp)
DKDEPEND(tiff)
DKDEPEND(glew)
DKDEPEND(sfml)
DKDEPEND(rmlui rmlui_debugger)

DKINCLUDE(${DKPROJECT})
DKINCLUDE(${DKPROJECT}/shell/include)

#LIST(APPEND WIN_LIBS shlwapi.lib)
WIN_DEBUG_LIB(shlwapi.lib)
WIN_RELEASE_LIB(shlwapi.lib)