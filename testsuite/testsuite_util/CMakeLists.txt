################################################################################
## IBIS/testsuite util project
##
## file: testsuite/vhdl/util/CMakeLists.txt
################################################################################
project(testsuite_util
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_library(${PROJECT_NAME})
add_library(testsuite::util ALIAS ${PROJECT_NAME})


target_sources(${PROJECT_NAME}
    PRIVATE
        src/cli_args.cpp
        src/dataset_loader.cpp
        src/basic_failure_diagnostic_fixture.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ibis::util
    Boost::headers
    CLI11::CLI11
)

if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    SYSTEM PUBLIC
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)
