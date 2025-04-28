# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  CMAKE_POLICY(SET CMP0141 NEW)
  #SET(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()





PROJECT ("SproutEngine")

# Include sub-projects.
ADD_SUBDIRECTORY ("SproutEngine")

ADD_SUBDIRECTORY ("SproutRuntime")


# --- End Testing Setup ---


SET (EXTERNAL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/Externals/)
SET (ENGINE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/Engine/)
SET (SPROUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/)
SET (RUNTIME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutRuntime/)
#MESSAGE ([<WARNING>]"Binary path: ${ENGINE_DIRECTORY}")