# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
CMAKE_MINIMUM_REQUIRED (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  CMAKE_POLICY(SET CMP0141 NEW)
  #SET(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()





PROJECT ("SproutEngine")


# Enable AddressSanitizer only for Debug builds
#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
   # string(APPEND CMAKE_C_FLAGS_DEBUG " /fsanitize=address")
    #string(APPEND CMAKE_CXX_FLAGS_DEBUG " /fsanitize=address")
   # message(STATUS "AddressSanitizer enabled for Debug build.")
#endif()


# Enable AddressSanitizer for MSVC builds (Debug and Release)
if(MSVC)
    string(APPEND CMAKE_C_FLAGS_DEBUG " /fsanitize=address")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " /fsanitize=address")
    string(APPEND CMAKE_C_FLAGS_RELEASE " /fsanitize=address")
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " /fsanitize=address")
    message(STATUS "AddressSanitizer flags applied for MSVC build (Debug and Release).")


    add_compile_options(/EHsc)

endif()


# Detect platform
if (WIN32)
    add_compile_definitions(SPROUT_PLATFORM_WINDOWS=1)
elseif (UNIX AND NOT APPLE)
    add_compile_definitions(SPROUT_PLATFORM_LINUX=1)
elseif (APPLE)
    add_compile_definitions(SPROUT_PLATFORM_MAC=1)
else()
    message(FATAL_ERROR "Unsupported platform!")
endif()



# Include sub-projects.
ADD_SUBDIRECTORY ("SproutEngine")

ADD_SUBDIRECTORY ("SproutRuntime")






# --- End Testing Setup ---


SET (EXTERNAL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/Externals/)
SET (ENGINE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/Engine/)
SET (SPROUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutEngine/)
SET (RUNTIME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SproutRuntime/)
#MESSAGE ([<WARNING>]"Binary path: ${ENGINE_DIRECTORY}")