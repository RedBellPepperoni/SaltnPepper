# DIRECTORY : SproutEngine/Engine/Math

SET(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

	
LIST(
	APPEND SRC_FILES
	"${CURRENT_DIR}/Vectors/DirectMath/Vector2_DX.cpp"
	"${CURRENT_DIR}/Vectors/DirectMath/Vector3_DX.cpp"
	"${CURRENT_DIR}/Quaternion.cpp"
	"${CURRENT_DIR}/Matrix4.cpp"
)

LIST(
	APPEND INC_FILES
	"${CURRENT_DIR}/Vectors/Vector.h"
	"${CURRENT_DIR}/Quaternion.h"
	"${CURRENT_DIR}/Matrix4.h"
	"${CURRENT_DIR}/MathFunctions.h"
	"${CURRENT_DIR}/MathDefinitions.h"
)


#Define Math as an OBJECT library
add_library(Math OBJECT ${SRC_FILES} ${INC_FILES})

# Set C++ standard
set_property(TARGET Math PROPERTY CXX_STANDARD 20)

# Set public include directory
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

