################################################################################
## EDA/doc project
##
## file: doc_ng/CMakeLists.txt
################################################################################

##> https://github.com/svenevs/exhale/blob/master/docs/reference/configs.rst#doxygen-execution-and-customization

## API documentation with Sphinx and Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION_NG "Create and install the HTML based API documentation (requires Doxygen & Sphinx)" ${DOXYGEN_FOUND})


if(${DOXYGEN_FOUND})
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
endif()


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
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source ${PY_ENV}/bin/activate>"
    COMMAND python -m ensurepip
    COMMAND python -m pip install --upgrade pip
    COMMAND pip install wheel --upgrade
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/script/py_requirements.txt requirements.txt
    COMMAND pip install --no-cache-dir -r requirements.txt --upgrade
    #COMMAND pip list
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
    VERBATIM
)

# the target for Python's virtual environment
add_custom_target(doc-ng-pyenv
    COMMENT "Setup Python's virtual environment."
    DEPENDS ${PY_ENV}
)


##
# target helper for running Sphinx-doc
#
# determine relative path to conf.py which is a required variable inside conf.py
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxy_output)
#file(RELATIVE_PATH DOXYGEN_OUTPUT_DIR_REL
#    # strange, but works. I would expect ${CMAKE_CURRENT_BINARY_DIR} ...
#    ${CMAKE_CURRENT_SOURCE_DIR}/source/conf.py ${DOXYGEN_OUTPUT_DIR}
#)
#message(STATUS "Doxygen's relative output path: ${DOXYGEN_OUTPUT_DIR_REL}")
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
        ${PY_ENV}
        ${TEST_MATRIX_SCRIPT}
        ${TEST_CASE_FILES_DEPENDENCY}
    # command batch
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source ${PY_ENV}/bin/activate>"
    COMMAND ${Python3_EXECUTABLE} ${TEST_MATRIX_SCRIPT}
        -i ${TEST_MATRIX_SCRIPT_INPUT} -o ${TEST_MATRIX_SCRIPT_OUTPUT}
        -f rst -p ${CMAKE_CURRENT_BINARY_DIR}/source/testsuite_parser_grammar.rst
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
)


# the target for generating the test case matrix only
add_custom_target(doc-ng-testmatrix
    COMMENT "Generate VHDL test case matrix for Spirit X3 parser rules"
    DEPENDS ${TEST_MATRIX_SCRIPT_OUTPUT}
)


##
# Call sphinx-build inside Python's virtual environment to generate the docs
# Note, doxygen doesn't create the path for 'WARN_LOGFILE'.
add_custom_command(OUTPUT ./output
    COMMENT "Generating API documentation using Sphinx + Exhale + Breathe + Doxygen"
    DEPENDS
        ${PY_ENV}
        ${CMAKE_CURRENT_BINARY_DIR}/source/.copy.tag
        ${TEST_MATRIX_SCRIPT}
        ${TEST_MATRIX_SCRIPT_OUTPUT}
    # command batch
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIR}
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/activate,source ${PY_ENV}/bin/activate>"
    COMMAND sphinx-build -M html ./source ./output
    COMMAND "$<IF:$<PLATFORM_ID:Windows>,${PY_ENV}/Scripts/deactivate,deactivate>"
    VERBATIM
)
message(STATUS "Sphinx path: ${CMAKE_CURRENT_BINARY_DIR}")

##
# the doc target self
add_custom_target(doc-ng
    COMMENT "Generating documentation"
    DEPENDS ./output
)
# also clean up output, CMake doesn't know about it.
# Note: This prevents from ninja's error about permission denied (on Windows)
set_target_properties(doc-ng
    PROPERTIES
        ADDITIONAL_CLEAN_FILES ./output
)
