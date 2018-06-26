################################################################################
## testsuite/common/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL Test Suite common project
################################################################################

project(testsuite_common LANGUAGES CXX)


set(TESTSUITE_COMMON_SOURCE
    src/data_set.cpp
)

add_library(${PROJECT_NAME} STATIC ${TESTSUITE_COMMON_SOURCE})
add_library(eda::testsuite_common ALIAS ${PROJECT_NAME})


# adjust include path
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    PRIVATE src)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)

## 
# Boost.Org 
# Spirit X3 is required for the parser - we are working on developer branch. 
# Nevertheless Spirit self depends on other headers, e..g boost.range
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})


# Since Boost.Test does not expose the argc/argv values outside of the
# test case we have to provide the path to the test case files manualy
configure_file(
    ${PROJECT_SOURCE_DIR}/include/testsuite/testsuite_prefix.hpp.in
    ${PROJECT_BINARY_DIR}/include/testsuite/testsuite_prefix.hpp
    @ONLY)


