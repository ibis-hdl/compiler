################################################################################
## EDA/testsuite common project
##
## file: testsuite/common/CMakeLists.txt
################################################################################

project(testsuite_common LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(testsuite::common ALIAS ${PROJECT_NAME})


# Ninja Build
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


if(EDA_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME} PRIVATE
    src/data_set.cpp
    src/failure_diagnostic_fixture.cpp
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
    eda::common
)


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${BOOST_UTF_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:      /W1>
    $<$<CXX_COMPILER_ID:GNU>:       -Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:     -Wall -Wextra>
)

