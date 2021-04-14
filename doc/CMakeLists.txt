################################################################################
## EDA/doc project
##
## file: doc/CMakeLists.txt
################################################################################

## API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(${DOXYGEN_FOUND})
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
endif()

##
# Doxygen configuration file(s)
set(DOXYGEN_PREDEFINED
    # same as sphinx-doc defaults, see [Mastering Doxygen](
    # https://exhale.readthedocs.io/en/latest/mastering_doxygen.html#additional-variables-with-important-impacts)
    "DOXYGEN_DOCUMENTATION_BUILD DOXYGEN_SHOULD_SKIP_THIS"
)
# quiet doxygen ("YES"|"NO")
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
# target helper to setup doc-{api,testsuite}
#
# Python's virtual environment is used to avoid pollution of user's Python directory.
# FixMe: Find a way to exclude the 'command' venv from clean target. Using ${PY_ENV}
#        as dependency results on an ninja error:  remove(doc/venv): Permission denied
#        (at least) on Windows. Using a 'tag' file approach as dependency calls each
#        time the 'command' to recreate the venv.
#
# See: using Python's [Virtual Environments and Packages](https://docs.python.org/3/tutorial/venv.html)
# and [Activating a virtual environment](https://pythonise.com/categories/python/python-virtual-environments-with-the-venv-command#activating-a-virtual-environment)
# self-bootstrap pip, see [Installation](https://pip.pypa.io/en/stable/installing/),
# and install requirements.
set(PY_ENV ${CMAKE_CURRENT_BINARY_DIR}/venv)

add_custom_command(OUTPUT ${PY_ENV}
    COMMENT "Setup Python's virtual environment to generate documentation."
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/script/py_requirements.txt
    # command batch
    COMMAND ${Python3_EXECUTABLE} -m venv ${PY_ENV}
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source;${PY_ENV}/bin/activate>"
    COMMAND python -m ensurepip
    COMMAND python -m pip install --upgrade pip
    COMMAND pip install wheel --upgrade
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/script/py_requirements.txt requirements.txt
    COMMAND pip install --no-cache-dir -r requirements.txt --upgrade
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
    COMMAND_EXPAND_LISTS
    #VERBATIM
)

# the target for Python's virtual environment
add_custom_target(doc-pyenv
    COMMENT "Setup Python's virtual environment."
    DEPENDS ${PY_ENV}
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
        ${PY_ENV}
        ${TEST_MATRIX_SCRIPT}
        ${TEST_CASE_FILES_DEPENDENCY}
    # command batch
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source;${PY_ENV}/bin/activate>"
    COMMAND ${Python3_EXECUTABLE} ${TEST_MATRIX_SCRIPT}
        -i ${TEST_MATRIX_SCRIPT_INPUT} -o ${TEST_MATRIX_SCRIPT_OUTPUT}
        -f grid -p ${CMAKE_CURRENT_SOURCE_DIR}/testsuite/readme.md
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
    COMMAND_EXPAND_LISTS
)


# the target for generating the test case matrix only
add_custom_target(doc-testsuite-parser-testmatrix
    COMMENT "Generate VHDL test case matrix for Spirit X3 parser rules"
    DEPENDS ${PY_ENV} ${TEST_MATRIX_SCRIPT_OUTPUT}
)


##
# The targets self: doc, doc-testsuite
add_custom_target(doc
    COMMENT "Generating API documentation with Doxygen"
    COMMAND ${DOXYGEN_EXECUTABLE} doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api
    VERBATIM
)
add_custom_target(doc-testsuite
    COMMENT "Generating TestSuite documentation with Doxygen"
    DEPENDS ${TEST_MATRIX_SCRIPT_OUTPUT}
    COMMAND ${DOXYGEN_EXECUTABLE} doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsuite
    VERBATIM
)
# also clean up test matrix output, CMake doesn't know about it.
# FixMe: This prevents from ninja's error about permission denied (on Windows)
# recreating is cheap ...
set_target_properties(doc-testsuite
    PROPERTIES
        ADDITIONAL_CLEAN_FILES ${TEST_MATRIX_SCRIPT_OUTPUT}
)
