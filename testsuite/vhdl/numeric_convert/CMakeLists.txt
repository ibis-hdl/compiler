################################################################################
## IBIS/testsuite VHDL numeric convert project
##
## file: testsuite/vhdl/numeric_convert/CMakeLists.txt
################################################################################

project(testrunner_vhdl_numeric_convert
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


add_test(NAME test_vhdl_numeric_conversion
    COMMAND
        ${PROJECT_NAME} --log_level=error
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
        testsuite::util
        Boost::headers
        Boost::system
        Boost::locale
        Boost::unit_test_framework
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_numeric_convert.cpp
        src/numeric_parser.cpp
        src/binary_string.cpp
        # concrete test cases
        src/test/bit_string_literal_test.cpp
        src/test/decimal_literal_test.cpp
		src/test/based_literal_test_ng.cpp
)


#set_source_files_properties(src/test_numeric_convert.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with precompiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_numeric_convert.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    SYSTEM PUBLIC
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
)
