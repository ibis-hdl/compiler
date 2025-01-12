################################################################################
## IBIS/testsuite misc project
##
## file: testsuite/misc/CMakeLists.txt
################################################################################
project(testrunner_misc
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})

add_test(NAME test_misc
    COMMAND
        ${PROJECT_NAME} # using ENV, old: --log_level=error
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Boost::headers
        ibis::vhdl
        testsuite::util
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/tests/test_diagnostic_printer.cpp
        src/test_main.cpp
)


# [Boost.Test linker error by use with pre-compiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_main.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
)
