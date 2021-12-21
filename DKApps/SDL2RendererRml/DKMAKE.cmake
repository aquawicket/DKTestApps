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
DKDEPEND(mobile_core_services)
file(GLOB_RECURSE RES_FILES "${DKPROJECT}/Samples/*")

if(DEBUG)
	dk_makeDirectory(${DKPROJECT}/${OS}/${DEBUG_DIR}/${APP_NAME}.app/assets)
	DKCOPY(${DKPROJECT}/Samples/ ${DKPROJECT}/${OS}/${DEBUG_DIR}/${APP_NAME}.app/Samples TRUE)
endif()
if(RELEASE)
	dk_makeDirectory(${DKPROJECT}/${OS}/${RELEASE_DIR}/${APP_NAME}.app/assets)
	DKCOPY(${DKPROJECT}/Samples/ ${DKPROJECT}/${OS}/${RELEASE_DIR}/${APP_NAME}.app/Samples TRUE)
endif()
add_custom_command(TARGET ${APP_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
              ${CMAKE_CURRENT_LIST_DIR}/Samples $<TARGET_FILE_DIR:ExampleTestTarget>
)