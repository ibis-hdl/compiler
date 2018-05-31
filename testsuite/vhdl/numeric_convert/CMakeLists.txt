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
    bit_string_literal_test.cpp
    decimal_literal_test.cpp
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


## Boost.Org's Spirit.X3 newer version is required from local clone
add_dependencies(${PROJECT_NAME} boost-spirit-x3)

# Boost.Org depend includes
include_directories(${SPIRIT_X3_INCLUDE_DIR})


## 
# Boost.Org UTF
# FixMe: numeric_parser.cpp depends for unkown reasons on boost::filesystem's
#        path::generic_string, path::codecvt, path::convert  
#        on MinGW
find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    Boost::system
    Boost::filesystem
)


## 
# CMake/CTest
add_test(NAME test_vhdl_numeric_conversion
    COMMAND ${PROJECT_NAME}
)