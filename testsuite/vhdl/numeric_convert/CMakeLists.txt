################################################################################
## testsuite/vhdl/numeric_convert/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite for converting parsed literals to numeric 
################################################################################

project(testrunner_vhdl_numeric LANGUAGES CXX)


set(NUMERIC_SOURCES
    test_numeric_convert.cpp
    numeric_parser.cpp
    bit_string_literal.cpp
)

add_executable(${PROJECT_NAME} ${NUMERIC_SOURCES})


# adjust include path
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


# increase limit especially for clang recursive template instantiation,
# otherwise exceedes maximum depth of 512
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -ftemplate-depth=1024)
endif()


## Boost.Org 
find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})

## EDA
# depends on ...
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    ${Boost_SYSTEM_LIBRARY}
)


## 
# CMake/CTest
add_test(NAME test_vhdl_numeric_conversion
    COMMAND ${PROJECT_NAME}
)
