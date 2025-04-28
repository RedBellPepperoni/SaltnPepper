# CMakeLists.txt for Engine/Core

# Define an interface library for the Core headers
add_library(Core INTERFACE)

# Add the current directory as an interface include directory
target_include_directories(Core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
