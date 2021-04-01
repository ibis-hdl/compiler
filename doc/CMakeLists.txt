################################################################################
## EDA/devel-doc project
##
## file: doc/CMakeLists.txt
################################################################################

## API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# python is required for Doxygen's INPUT_FILTER
find_package(Python3 COMPONENTS Interpreter)


set(doxygen_definition_list
    # same as sphinx-doc defaults, see [Mastering Doxygen](
    # https://exhale.readthedocs.io/en/latest/mastering_doxygen.html#additional-variables-with-important-impacts)
    "DOXYGEN_DOCUMENTATION_BUILD DOXYGEN_SHOULD_SKIP_THIS"
)
foreach(doxygen_def ${doxygen_definition_list})
    set(doxygen_definitions "${doxygen_definitions} \"${doxygen_def}\"")
endforeach()


# API
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/api/doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/api/doxyfile
    @ONLY
)

# TestSuite
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/testsuite/doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/testsuite/doxyfile
    @ONLY
)


# Maybe check [doxygen_add_docs()](https://cmake.org/cmake/help/v3.11/module/FindDoxygen.html)
add_custom_target(doc
    COMMENT "Generating API documentation with Doxygen"
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/api
    COMMAND
        ${DOXYGEN_EXECUTABLE} doxyfile
    VERBATIM
)
add_custom_target(doc-testsuite
    COMMENT "Generating TestSuite documentation with Doxygen"
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}/testsuite
    COMMAND
        ${DOXYGEN_EXECUTABLE} doxyfile
    VERBATIM
)


if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    if(NOT Python3_Interpreter_FOUND)
        # for Doxygen's INPUT_FILTER
        message(FATAL_ERROR "Python3 is needed to build the documentation.")
    endif()
endif()



##
# Generate the VHDL parser grammar rules TestMatrix
# Requirements:
# - python3
# - packages:
#   - tabulate
#
# Note, if the package(s) aren't found, they are installed using pip.
# Therefore virtualenv is detected and pip args accordingly set.
#
# FixMe: This is a copy&paste version of former exta target
# from testsuite/vhdl/parser_rules/CMakeLists.txt. It should be
# run inside Python's venv and split the several test case into
# own files, included by doxygen generation.
find_package(Python3 COMPONENTS Interpreter REQUIRED)

if(DEFINED ENV{VIRTUAL_ENV} OR DEFINED ENV{CONDA_PREFIX})
    set(_pip_args)
else()
    set(_pip_args "--user")
endif()
set(_pypkg_names "tabulate")

execute_process(
    COMMAND
        ${Python3_EXECUTABLE} -m pip install ${_pip_args} ${_pypkg_names}
)

set(TEST_MATRIX_GENERATOR        ${CMAKE_CURRENT_SOURCE_DIR}/script/gen_test_matrix.py)
set(TEST_MATRIX_GENERATOR_INPUT  ${CMAKE_SOURCE_DIR}/testsuite/vhdl/parser_rules/test_data)
set(TEST_MATRIX_GENERATOR_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/testsuite/parser_test_data)

file(GLOB_RECURSE TEST_CASE_FILES_DEPENDENCY
    LIST_DIRECTORIES true
    "${TEST_MATRIX_GENERATOR_INPUT}" "*.expected"
)
add_custom_command(
    TARGET
        doc-testsuite PRE_BUILD
    COMMAND
        ${Python3_EXECUTABLE} ${TEST_MATRIX_GENERATOR} -I ${TEST_MATRIX_GENERATOR_INPUT} -O ${TEST_MATRIX_GENERATOR_OUTPUT}
    DEPENDS
        ${TEST_MATRIX_GENERATOR} ${TEST_CASE_FILES_DEPENDENCY}
    BYPRODUCT
        ${TEST_MATRIX_GENERATOR_OUTPUT}
    COMMENT
        "Generate VHDL Parser TestCase Matrix (RST)"
)

set_source_files_properties(
    ${TEST_MATRIX_GENERATOR_OUTPUT}
        PROPERTIES GENERATED TRUE
)

