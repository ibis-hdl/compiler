################################################################################
## IBIS/testsuite VHDL syntax project
##
## file: testsuite/vhdl/syntax/CMakeLists.txt
################################################################################

project(testrunner_vhdl_syntax
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


# Variables used to configure ctest project, also compile time builtin settings
set(TESTSUITE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test_data")
set(TESTSUITE_INPUT_EXTENSION ".vhdl")
set(TESTSUITE_EXPECTED_EXTENSION ".expected")
set(TESTSUITE_DESTINATION_DIR "${CMAKE_BINARY_DIR}/testsuite_result/vhdl/syntax")
set(TESTSUITE_OUTPUT_EXTENSION ".result")

add_test(NAME test_vhdl_syntax
    COMMAND
        ${PROJECT_NAME} --log_level=error --
        --source-dir=${TESTSUITE_SOURCE_DIR}
        --destination-dir=${TESTSUITE_DESTINATION_DIR}
        --input-extension=${TESTSUITE_INPUT_EXTENSION}
        --output-extension=${TESTSUITE_OUTPUT_EXTENSION}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
    PRIVATE
        testsuite::util
        Boost::headers
        Boost::system
        Boost::locale
        Boost::unit_test_framework
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


configure_file(
    ${PROJECT_SOURCE_DIR}/src/dataset_builtin.cpp.in
    ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
    @ONLY
)
configure_file(
    ${PROJECT_SOURCE_DIR}/src/failure_diagnostic_fixture_builtin.cpp.in
    ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
    @ONLY
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_vhdl_syntax.cpp
        src/failure_diagnostic_fixture.cpp ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
        src/dataset.cpp ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
        # concrete test cases
        src/test/label_check_test.cpp
        src/test/keyword_match_test.cpp ## FixMe [CMake]: requires more than 10GB!
)
# https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html
set_target_properties(${PROJECT_NAME} PROPERTIES
    UNITY_BUILD_MODE BATCH
    UNITY_BUILD_BATCH_SIZE 3
)


#set_source_files_properties(src/test_vhdl_syntax.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with precompiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_vhdl_syntax.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_10240MiB
)


if(IBIS_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
