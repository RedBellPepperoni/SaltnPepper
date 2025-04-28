


add_executable(SproutRuntime "SproutRuntime.cpp" "SproutRuntime.hpp")
TARGET_LINK_LIBRARIES(SproutRuntime PRIVATE SproutEngine SproutEngineCore)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  SET_PROPERTY(TARGET SproutRuntime PROPERTY CXX_STANDARD 20)
endif()
