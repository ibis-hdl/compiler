################################################################################
## IBIS/doc project
##
## file: doc_ng/CMakeLists.txt
################################################################################

##> https://github.com/svenevs/exhale/blob/master/docs/reference/configs.rst#doxygen-execution-and-customization

## API documentation with Sphinx and Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION_NG "Create and install the HTML based API documentation (requires Doxygen & Sphinx)" ${DOXYGEN_FOUND})

if(${BUILD_DOCUMENTATION_NG})
    # require at least Doxygen 1.9
    if (DOXYGEN_VERSION VERSION_LESS 1.9)
        message(FATAL_ERROR "Doxygen version must be at least 1.9!")
    endif()
endif()


# setup the target for Python's virtual environment
# CMake way doesn't work any more: 
#   https://gist.github.com/ibis-hdl/83d93bf891f5f405cddd9fb0c32d60c3
# pip install --no-cache-dir -r doc_ng/requirements.txt --upgrade

##
# target helper for running Sphinx-doc
#
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxy_output)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
    ${CMAKE_CURRENT_BINARY_DIR}/source/conf.py
    @ONLY
)

# copy resources to build directory since Sphinx works with relative paths to conf.py
# Note, file(COPY ... ) works on configuration time only.
file(GLOB SPHINX_DOC_FILES
    LIST_DIRECTORIES false
    ${CMAKE_CURRENT_SOURCE_DIR}/*.rst
)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/source/.copy.tag
    COMMENT "Copy Sphinx files to build directory"
    DEPENDS
        ${SPHINX_DOC_FILES} _static _templates
        ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/source/conf.py
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SPHINX_DOC_FILES} ${CMAKE_CURRENT_BINARY_DIR}/source
    COMMAND ${CMAKE_COMMAND} -E copy_directory _static ${CMAKE_CURRENT_BINARY_DIR}/source/_static
    COMMAND ${CMAKE_COMMAND} -E copy_directory _templates ${CMAKE_CURRENT_BINARY_DIR}/source/_templates
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/source/.copy.tag
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # required!
    VERBATIM
)


##
# Generate the VHDL parser grammar rules TestMatrix
# Requirements (fulfilled by Python's virtual environments setup before):
# - python3
# - packages:
#   - tabulate
set(TEST_MATRIX_SCRIPT        ${CMAKE_SOURCE_DIR}/doc/script/gen_test_matrix.py)
set(TEST_MATRIX_SCRIPT_INPUT  ${CMAKE_SOURCE_DIR}/testsuite/vhdl/parser_rules/test_data)
set(TEST_MATRIX_SCRIPT_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/source/parser_test_data)

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
        -f rst -p ${CMAKE_CURRENT_BINARY_DIR}/source/testsuite_parser_grammar.rst
    COMMAND_EXPAND_LISTS
)


# the target for generating the test case matrix only
add_custom_target(doc-ng-testmatrix
    COMMENT "Generate VHDL test case matrix for Spirit X3 parser rules"
    DEPENDS
        ${TEST_MATRIX_SCRIPT_OUTPUT}
)
# Clean up output, CMake doesn't know about it. This also prevents from ninja's error
# about permission denied (on Windows)
set_target_properties(doc-ng-testmatrix
    PROPERTIES
        ADDITIONAL_CLEAN_FILES ${TEST_MATRIX_SCRIPT_OUTPUT}
)


##
# Call sphinx-build inside Python's virtual environment to generate the docs
# Note, doxygen doesn't create the path for 'WARN_LOGFILE'.
add_custom_command(OUTPUT ./output
    COMMENT "Generating API documentation using Sphinx + Exhale + Breathe + Doxygen"
    DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/source/.copy.tag
        ${TEST_MATRIX_SCRIPT}
        ${TEST_MATRIX_SCRIPT_OUTPUT}
    # command batch
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
    COMMAND sphinx-build -M html ./source ./output
    COMMAND_EXPAND_LISTS
    #VERBATIM
)
message(STATUS "Sphinx path: ${CMAKE_CURRENT_BINARY_DIR}")

##
# the doc target self
add_custom_target(doc-ng
    COMMENT "Generating documentation"
    DEPENDS ./output
)
# Clean up output, CMake doesn't know about it. This also prevents from ninja's error
# about permission denied (on Windows)
set_target_properties(doc-ng
    PROPERTIES
        ADDITIONAL_CLEAN_FILES ./output
)
