# DIRECTORY : SproutEngine/Engine/Math

SET(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

	
LIST(
	APPEND SRC_FILES
	"${CURRENT_DIR}/Vectors/Vector2.cpp"
	"${CURRENT_DIR}/Vectors/Vector3.cpp"
	"${CURRENT_DIR}/Quaternion.cpp"
	"${CURRENT_DIR}/Matrix4.cpp"
)

LIST(
	APPEND INC_FILES
	"${CURRENT_DIR}/Vectors/Vector2.hpp"
	"${CURRENT_DIR}/Vectors/Vector3.hpp"
	"${CURRENT_DIR}/Quaternion.hpp"
	"${CURRENT_DIR}/Matrix4.hpp"
	"${CURRENT_DIR}/MathFunctions.hpp"
	"${CURRENT_DIR}/MathDefinitions.hpp"
)


#Define Math as an OBJECT library
add_library(Math OBJECT ${SRC_FILES} ${INC_FILES})

# Set C++ standard
set_property(TARGET Math PROPERTY CXX_STANDARD 20)

# Set public include directory
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

