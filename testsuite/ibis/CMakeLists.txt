################################################################################
## EDA/testsuite ibis project
##
## file: testsuite/ibis/CMakeLists.txt
################################################################################

#project(testrunner_ibis)

add_test(NAME test_ibis_cli_1
    WORKING_DIRECTORY 
        ${CMAKE_BUILD_DIR}
    COMMAND 
        ${CMAKE_BINARY_DIR}/bin/ibis ${CMAKE_SOURCE_DIR}/Readme.txt -v
)

add_test(NAME test_ibis_cli_locale
    WORKING_DIRECTORY 
        ${CMAKE_BUILD_DIR}
    COMMAND 
        ${CMAKE_BINARY_DIR}/bin/ibis ${CMAKE_SOURCE_DIR}/Readme.txt -v
        --locale-dir "${CMAKE_BINARY_DIR}/l10n"
)

add_test(NAME test_ibis_cli_locale_env
    WORKING_DIRECTORY 
        ${CMAKE_BUILD_DIR}
    COMMAND 
        ${CMAKE_BINARY_DIR}/bin/ibis ${CMAKE_SOURCE_DIR}/Readme.txt -v
)
set_tests_properties(test_ibis_cli_locale_env PROPERTIES 
    ENVIRONMENT "EDA_LOCALE_DIR=${CMAKE_BINARY_DIR}/l10n"
)

