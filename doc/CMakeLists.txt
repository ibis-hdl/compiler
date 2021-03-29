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
    COMMAND
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/api/doxyfile
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)
add_custom_target(doc-testsuite
    COMMAND
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/testsuite/doxyfile
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating TestSuite documentation with Doxygen"
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
