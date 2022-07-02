################################################################################
## IBIS/testsuite ibis project
##
## file: testsuite/spirit_x3/CMakeLists.txt
################################################################################

project(testrunner_x3)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_spirit_x3.cpp
        src/test/lexical_elements.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::unit_test_framework    
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")

add_test(NAME test_x3_charset
    WORKING_DIRECTORY
        ${CMAKE_BUILD_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ${CMAKE_CURRENT_SOURCE_DIR}/TestInput.vhdl
)

