################################################################################
## IBIS/testsuite ibis project
##
## file: testsuite/ibis/CMakeLists.txt
################################################################################

#project(testrunner_ibis)

add_test(NAME test_ibis_cli_1
    WORKING_DIRECTORY
        ${CMAKE_BUILD_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ${CMAKE_CURRENT_SOURCE_DIR}/TestInput.txt
)


add_test(NAME test_ibis_cli_locale
    WORKING_DIRECTORY
        ${CMAKE_BUILD_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ${CMAKE_CURRENT_SOURCE_DIR}/TestInput.txt
        --locale-dir "${CMAKE_BINARY_DIR}/l10n"
)


add_test(NAME test_ibis_cli_locale_env
    WORKING_DIRECTORY
        ${CMAKE_BUILD_DIR}
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ibis ${CMAKE_CURRENT_SOURCE_DIR}/TestInput.txt
)

set_tests_properties(test_ibis_cli_locale_env PROPERTIES
    ENVIRONMENT "IBIS_LOCALE_DIR=${CMAKE_BINARY_DIR}/l10n"
)

