################################################################################
## IBIS/doc project
##
## file: doc/CMakeLists.txt
################################################################################

## API documentation with Doxygen
find_package(Doxygen OPTIONAL_COMPONENTS dot)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(${BUILD_DOCUMENTATION})
    # require at least Doxygen 1.9
    if (DOXYGEN_VERSION VERSION_LESS 1.9)
        message(FATAL_ERROR "Doxygen version must be at least 1.9!")
    endif()
endif()


##
# Doxygen configuration file(s), see doxyfile.in for configurable settings below
#
set(DOXYGEN_PREDEFINED
    # same as sphinx-doc defaults, see [Mastering Doxygen](
    # https://exhale.readthedocs.io/en/latest/mastering_doxygen.html#additional-variables-with-important-impacts)
    "DOXYGEN_DOCUMENTATION_BUILD DOXYGEN_SHOULD_SKIP_THIS"
)
set(DOXYGEN_QUIET "YES")

# API Doxyfile
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/api/doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/api/doxyfile
    @ONLY
)

# TestSuite Doxyfile
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/testsuite/doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/testsuite/doxyfile
    @ONLY
)


##
# Generate the VHDL parser grammar rules TestMatrix
# Requirements (fulfilled by Python's virtual environments setup before):
# - python3
# - packages:
#   - tabulate
set(TEST_MATRIX_SCRIPT        ${CMAKE_CURRENT_SOURCE_DIR}/script/gen_test_matrix.py)
set(TEST_MATRIX_SCRIPT_INPUT  ${CMAKE_SOURCE_DIR}/testsuite/vhdl/parser_rules/test_data)
set(TEST_MATRIX_SCRIPT_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/testsuite/parser_test_data)

file(GLOB_RECURSE TEST_CASE_FILES_DEPENDENCY
    LIST_DIRECTORIES true
    ${TEST_MATRIX_SCRIPT_INPUT} *.(input|expected)
)
add_custom_command(OUTPUT ${TEST_MATRIX_SCRIPT_OUTPUT}
    COMMENT "Generate VHDL Parser TestCase Matrix (RST)"
    DEPENDS
        ${TEST_MATRIX_SCRIPT}
        ${TEST_CASE_FILES_DEPENDENCY}
    # command batch
    COMMAND python ${TEST_MATRIX_SCRIPT}
        -i ${TEST_MATRIX_SCRIPT_INPUT} -o ${TEST_MATRIX_SCRIPT_OUTPUT}
        -f grid -p ${CMAKE_CURRENT_SOURCE_DIR}/testsuite/readme.md
    COMMAND_EXPAND_LISTS
)


# the target for generating the test case matrix only
add_custom_target(doc-testsuite-parser-testmatrix
    COMMENT "Generate VHDL test case matrix for Spirit X3 parser rules"
    DEPENDS
        ${TEST_MATRIX_SCRIPT_OUTPUT}
)


##
# The targets self: doc, doc-testsuite
add_custom_target(doc
    COMMENT "Generating API documentation with Doxygen ${DOXYGEN_VERSION}"
    COMMAND doxygen doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api
    VERBATIM
)
add_custom_target(doc-testsuite
    COMMENT "Generating TestSuite documentation with Doxygen ${DOXYGEN_VERSION}"
    DEPENDS
        ${TEST_MATRIX_SCRIPT_OUTPUT}
    COMMAND doxygen doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsuite
    VERBATIM
)
# also clean up test matrix output, CMake doesn't know about it.
# FixMe [CMake]: This prevents from ninja's error about permission denied (on Windows)
# recreating is cheap ...
set_target_properties(doc-testsuite
    PROPERTIES
        ADDITIONAL_CLEAN_FILES ${TEST_MATRIX_SCRIPT_OUTPUT}
)
