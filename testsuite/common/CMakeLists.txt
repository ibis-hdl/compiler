################################################################################
## testsuite/common/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL Test Suite common project
################################################################################

project(testsuite_common LANGUAGES CXX)


add_library(${PROJECT_NAME} STATIC "")
add_library(testsuite::common ALIAS ${PROJECT_NAME})


# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


target_sources(${PROJECT_NAME} PRIVATE
    src/data_set.cpp
    src/failure_diagnostic_fixture.cpp
)


add_dependencies(${PROJECT_NAME} boost-utf)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
    eda::common
)


find_package(Boost REQUIRED)


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>
)


target_compile_options(${PROJECT_NAME} 
    PRIVATE -Wall -Wextra
)

