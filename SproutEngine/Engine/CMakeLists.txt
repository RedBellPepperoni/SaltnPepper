# DIRECTORY : SaltnPepperEngine/Engine

SET(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

ADD_SUBDIRECTORY("${CURRENT_DIR}/Utilities")
ADD_SUBDIRECTORY("${CURRENT_DIR}/Math")



# Define an interface library to bundle Engine components
ADD_LIBRARY(SproutEngineCore INTERFACE)

# Link Utilities and Math targets to the interface library
TARGET_LINK_LIBRARIES(SproutEngineCore INTERFACE Utilities Math)


SET (SRC_FILES ${SRC_FILES} PARENT_SCOPE )
SET (INC_FILES ${INC_FILES} PARENT_SCOPE )