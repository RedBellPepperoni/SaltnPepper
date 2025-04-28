# CMakeList.txt : CMake project for SproutEngine, include source and define
# project specific logic here.



SET (EXTERNAL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Externals/)
SET (ENGINE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Engine/)








#SET(SRC_FILES "SproutEngine.cpp" )
#SET(INC_FILES  "SproutEngine.h")

ADD_SUBDIRECTORY(${ENGINE_DIRECTORY})
ADD_SUBDIRECTORY(${EXTERNAL_DIRECTORY})




ADD_LIBRARY(SproutEngine STATIC $<TARGET_OBJECTS:Math> $<TARGET_OBJECTS:Utilities>)
TARGET_LINK_LIBRARIES(SproutEngine PUBLIC SproutEngineCore)
TARGET_LINK_LIBRARIES(SproutEngine PUBLIC spdlog)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  SET_PROPERTY(TARGET SproutEngine PROPERTY CXX_STANDARD 20)
endif()




# TODO: Add tests and install targets if needed.

set(CMAKE_CXX_FLAGS "/utf-8")
set(CMAKE_C_FLAGS "/utf-8")




# include Paths for External Headers
TARGET_INCLUDE_DIRECTORIES(SproutEngine PUBLIC ${EXTERNAL_DIRECTORY})

# include Paths for Engine Headers
TARGET_INCLUDE_DIRECTORIES(SproutEngine PUBLIC ${ENGINE_DIRECTORY})

# include Paths for SproutEngine Headers
TARGET_INCLUDE_DIRECTORIES(SproutEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# --- Testing Setup ---
ENABLE_TESTING() 

# Add Google Test from local source
ADD_SUBDIRECTORY(${EXTERNAL_DIRECTORY}googletest/)

# Add the Tests subdirectory
ADD_SUBDIRECTORY(${SPROUT_DIRECTORY}Tests/)


MESSAGE ([<WARNING>]"Binary path: ${ENGINE_DIRECTORY}")
#SUBDIRS(${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/Externals/spdlog)




