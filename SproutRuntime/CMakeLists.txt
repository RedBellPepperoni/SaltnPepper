

add_executable(SproutRuntime "SproutRuntime.cpp" "SproutRuntime.hpp")
TARGET_LINK_LIBRARIES(SproutRuntime PRIVATE SproutEngine SproutEngineCore)