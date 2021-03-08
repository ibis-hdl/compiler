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
    "DOXYGEN=1"
)
foreach(doxygen_def ${doxygen_definition_list})
    set(doxygen_definitions "${doxygen_definitions} \"${doxygen_def}\"")
endforeach()

    
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in 
    ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
    @ONLY
)


# Maybe check [doxygen_add_docs()](https://cmake.org/cmake/help/v3.11/module/FindDoxygen.html)
add_custom_target(doc
    COMMAND
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
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
