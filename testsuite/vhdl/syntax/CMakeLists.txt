################################################################################
## EDA/testsuite VHDL syntax project
##
## file: testsuite/vhdl/syntax/CMakeLists.txt
################################################################################

project(testrunner_vhdl_syntax LANGUAGES CXX)


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
        eda::vhdl_parser
    PRIVATE
        testsuite::util
        Boost::system
        Boost::locale
        Boost::unit_test_framework

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


if(DEVELOPER_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} external-boost-utf)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_vhdl_syntax.cpp
        src/failure_diagnostic_fixture.cpp ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
        src/dataset.cpp ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
        # concrete test cases
        src/test/label_check_test.cpp
        src/test/keyword_match_test.cpp ## FixMe: requires more than 10GB!
)


set_source_files_properties(src/test_vhdl_syntax.cpp
    APPEND PROPERTIES
        # Failed to link Boost UTF with Windows/Clang, Linux works
        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
)
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


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/syntax/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/syntax/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        # don't allow automatically select which libraries to link against
        $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)
