################################################################################
## IBIS/testsuite ibis project
##
## file: testsuite/frontend/CMakeLists.txt
################################################################################

#project(testrunner_ibis)

# common test
add_test(NAME test_ibis_cli_1
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ./TestInput.vhdl
)


# test with explicit locale settings
add_test(NAME test_ibis_cli_locale
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ./TestInput.vhdl
        --locale-dir "${CMAKE_BINARY_DIR}/l10n"
)


# test with locale settings using ENV variable
add_test(NAME test_ibis_cli_locale_env
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ./TestInput.vhdl
)

set_tests_properties(test_ibis_cli_locale_env PROPERTIES
    ENVIRONMENT "IBIS_HDL_LOCALE_DIR=${CMAKE_BINARY_DIR}/l10n"
)

