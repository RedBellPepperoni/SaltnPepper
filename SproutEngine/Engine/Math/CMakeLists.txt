set(CURRENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SPROUT_MATH_BACKEND "DIRECTX" CACHE STRING "Math backend (GLM or DIRECTX)")
set_property(CACHE SPROUT_MATH_BACKEND PROPERTY STRINGS GLM DIRECTX)

if(SPROUT_MATH_BACKEND STREQUAL "GLM")

    add_library(Math OBJECT
        "${CURRENT_DIR}/Vectors/GLMath/Vector2_GLM.cpp"
    )

    target_include_directories(Math PUBLIC ${CURRENT_DIR})

    target_compile_definitions(Math PUBLIC
        SPROUT_MATH_GLM=1
        SPROUT_MATH_DIRECTX=0
    )

    set_property(TARGET Math PROPERTY CXX_STANDARD 20)

elseif(SPROUT_MATH_BACKEND STREQUAL "DIRECTX")

    add_library(Math OBJECT
        "${CURRENT_DIR}/Vectors/DirectMath/Vector2_DX.cpp"
        "${CURRENT_DIR}/Vectors/DirectMath/Vector3_DX.cpp"
        "${CURRENT_DIR}/Quaternion.cpp"
        "${CURRENT_DIR}/Matrix4.cpp"
    )

    target_include_directories(Math PUBLIC ${CURRENT_DIR})

    target_compile_definitions(Math PUBLIC
        SPROUT_MATH_GLM=0
        SPROUT_MATH_DIRECTX=1
    )

    set_property(TARGET Math PROPERTY CXX_STANDARD 20)

else()
    message(FATAL_ERROR "Unknown SPROUT_MATH_BACKEND: '${SPROUT_MATH_BACKEND}'")
endif()