# CMakeLists.txt for SproutEngine Tests

cmake_minimum_required(VERSION 3.16)
SET (TEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

# Define the test executable
add_executable(SproutEngineTests 
    ${TEST_DIRECTORY}Test_Vector2.cpp
    
)

# Link libraries
target_link_libraries(SproutEngineTests PRIVATE 
    gtest         # Link gtest library
    gtest_main    # Link gtest_main library (provides main())
    SproutEngine_Engine 
)

# Include directories for the tests
target_include_directories(SproutEngineTests PRIVATE 
    ../Engine 
)

# Discover tests automatically using CTest
include(GoogleTest)
gtest_discover_tests(SproutEngineTests)
