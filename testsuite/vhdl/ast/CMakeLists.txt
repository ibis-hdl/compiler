################################################################################
## IBIS/testsuite VHDL AST project
##
## file: testsuite/vhdl/ast/CMakeLists.txt
################################################################################

project(testrunner_vhdl_ast
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


add_test(NAME test_ast
    COMMAND
        ${PROJECT_NAME} --log_level=error --
        --source-dir=${PROJECT_SOURCE_DIR}/test_data
)


# Variables used to configure ctest project, also compile time builtin settings
set(TESTSUITE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/test_data)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/ast/compile_builtin.hpp.in"
    "${PROJECT_BINARY_DIR}/include/testsuite/vhdl/ast/compile_builtin.hpp"
    @ONLY
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
        testsuite::util
        Boost::headers
        Boost::system
        Boost::unit_test_framework
        # cope with "fatal error LNK2011: precompiled object not linked in"
        "$<$<CXX_COMPILER_ID:MSVC>:testsuite_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/Verbose")


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_ast.cpp
        src/position_cache_fixture.cpp
        # concrete test cases
        src/test/position_cache_test_1.cpp
        src/test/position_cache_test_2.cpp
        src/test/literal_printer_test.cpp
)


#set_source_files_properties(src/test_ast.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with pre-compiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_ast.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


if(${PROJECT_NAME}_PCH)
    # override testsuite_pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/ast/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl/ast/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM testsuite_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    SYSTEM PUBLIC
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
)
