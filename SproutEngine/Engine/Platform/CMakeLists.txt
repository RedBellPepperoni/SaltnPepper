# DIRECTORY : SproutEngine/Engine/Platform

SET(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")



LIST(
	APPEND INC_FILES
	"${CURRENT_DIR}/Platform.h"
	"${CURRENT_DIR}/GenericPlatformTypes.h"
	"${CURRENT_DIR}/Windows/WindowsPlatform.h"
)


#Define Platform as an INTERFACE library
add_library(Platform INTERFACE)


# Set public include directory
target_include_directories(Platform INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

