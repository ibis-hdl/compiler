################################################################################
## IBIS/testsuite VHDL grammar project
##
## file: testsuite/vhdl/grammar/CMakeLists.txt
################################################################################

project(testrunner_vhdl_grammar
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]"
)


add_executable(${PROJECT_NAME})


add_test(NAME test_vhdl_grammar
    COMMAND
        ${PROJECT_NAME} --log_level=error
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
        testsuite::util
        Boost::headers
        Boost::locale
        Boost::unit_test_framework
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_grammar.cpp
        src/testsuite_parse.cpp
        # concrete test cases
        src/test/test_bit_string_literal.cpp
)
# https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html
set_target_properties(${PROJECT_NAME} PROPERTIES
    UNITY_BUILD_MODE BATCH
    UNITY_BUILD_BATCH_SIZE 3
)

# [Boost.Test linker error by use with pre-compiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_grammar.cpp
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
