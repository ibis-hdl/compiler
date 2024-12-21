################################################################################
## IBIS/testsuite VHDL grammar project
##
## file: testsuite/vhdl/grammar/CMakeLists.txt
################################################################################

project(testrunner_vhdl_grammar LANGUAGES CXX)


add_executable(${PROJECT_NAME})


# Variables used to configure ctest project, also compile time builtin settings
set(TESTSUITE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test_data")
set(TESTSUITE_INPUT_EXTENSION ".input")
set(TESTSUITE_EXPECTED_EXTENSION ".expected")
set(TESTSUITE_DESTINATION_DIR "${CMAKE_BINARY_DIR}/testsuite_result/vhdl/grammar_rules")
set(TESTSUITE_OUTPUT_EXTENSION ".result")

add_test(NAME test_vhdl_grammar
    COMMAND
        ${PROJECT_NAME} --log_level=error --
        --source-dir=${TESTSUITE_SOURCE_DIR}
        --input-extension=${TESTSUITE_INPUT_EXTENSION}
        --expected-extension=${TESTSUITE_EXPECTED_EXTENSION}
        --destination-dir=${TESTSUITE_DESTINATION_DIR}
        --output-extension=${TESTSUITE_OUTPUT_EXTENSION}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
        fmt::fmt
    PRIVATE
        testsuite::util
        Boost::system
        Boost::locale
        Boost::unit_test_framework
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:testsuite_pch>"
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


if(DEVELOPER_EXTERNAL_BOOST_SPIRIT)
    add_dependencies(${PROJECT_NAME} external-boost-spirit)
endif()
if(DEVELOPER_EXTERNAL_BOOST_TEST)
    add_dependencies(${PROJECT_NAME} external-boost-test)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_vhdl_grammar.cpp
        src/failure_diagnostic_fixture.cpp ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
        src/dataset.cpp ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
        src/testsuite_parse.cpp
        src/test/literal.cpp
        src/test/simple.cpp
)


#set_source_files_properties(src/test_vhdl_parser.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with precompiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_vhdl_parser.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_3072MiB
)


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)
