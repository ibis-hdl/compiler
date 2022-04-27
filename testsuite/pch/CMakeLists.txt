################################################################################
## IBIS/testsuite pch library project
##
## file: testsuite/pch/CMakeLists.txt
################################################################################

project(testsuite_pch LANGUAGES CXX)


add_library(${PROJECT_NAME} OBJECT)
add_library(testsuite::pch ALIAS ${PROJECT_NAME})


# see [PCH: Unclear error when reusing precompiled headers from interface library](
# https://gitlab.kitware.com/cmake/cmake/-/issues/20288)
file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/pch_dummy.cpp
)


target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/testsuite/pch_default.hpp>
        $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/testsuite/pch_ibis.hpp>
)


# Note, target_link_libraries(... ibis::common testsuite::util) doesn't work here
# since this would add cyclic dependencies
target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        # ibis source
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/common/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/source/common/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/vhdl/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/frontend/include>
        # ibis testsuite
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/testsuite/util/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/testsuite/vhdl/ast/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/testsuite/vhdl/numeric_convert/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/testsuite/vhdl/parser_rules/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/testsuite/vhdl/syntax/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_SPIRIT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${STRONG_TYPE_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CLI11_INCLUDE_DIR}>
)
