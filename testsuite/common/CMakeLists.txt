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
add_library(testsuite::common ALIAS ${PROJECT_NAME})


# Since Boost.Test does not expose the argc/argv values outside of the
# test case we have to provide the path to the test case files manualy
configure_file(
    ${PROJECT_SOURCE_DIR}/include/testsuite/testsuite_prefix.hpp.in
    ${PROJECT_BINARY_DIR}/include/testsuite/testsuite_prefix.hpp
    @ONLY)


## 
# Boost.Org 
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
)


target_compile_options(${PROJECT_NAME} 
    PRIVATE -Wall -Wextra
)





