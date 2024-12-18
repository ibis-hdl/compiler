################################################################################
## IBIS/pch library project
##
## file: source/pch/CMakeLists.txt
################################################################################

project(ibis_pch LANGUAGES CXX)


# see [PCH: Unclear error when reusing precompiled headers from interface library](
# https://gitlab.kitware.com/cmake/cmake/-/issues/20288)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp)

add_library(${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp)
add_library(ibis::pch ALIAS ${PROJECT_NAME})


target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/ibis/pch_default.hpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${strong_type_INCLUDE_DIR}>
)


if(DEVELOPER_BOOST_SPIRIT_X3_DEBUG)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG
    )
endif()
