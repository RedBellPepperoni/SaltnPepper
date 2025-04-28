# DIRECTORY : SaltnPepperEngine/Engine/Utilities

SET(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

	
LIST(
	APPEND SRC_FILES
	"${CURRENT_DIR}/Logging/Log.cpp"
)

LIST(
	APPEND INC_FILES
	"${CURRENT_DIR}/Logging/Log.hpp"
)

# Define Utilities as an OBJECT library
add_library(Utilities OBJECT ${SRC_FILES} ${INC_FILES})

# Set C++ standard
set_property(TARGET Utilities PROPERTY CXX_STANDARD 20)

# Set public include directory
target_include_directories(Utilities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Remove old way of propagating sources/includes
# SET (SRC_FILES ${SRC_FILES} PARENT_SCOPE )
# SET (INC_FILES ${INC_FILES} PARENT_SCOPE )