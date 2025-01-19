################################################################################
## IBIS/vhdl project
##
## file: source/vhdl/CMakeLists.txt
################################################################################

project(ibis_vhdl
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_library(${PROJECT_NAME})
add_library(ibis::vhdl ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ibis::common
        # fmt::fmt
        range-v3::range-v3
        Boost::headers
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/ast/ast_formatter.cpp
        src/ast/ast_printer.cpp
        src/ast/ast_stats.cpp
        src/ast/pretty_node_name.cpp

        src/ast/numeric_convert.cpp
        src/ast/numeric_convert/convert_bit_string.cpp
        src/ast/numeric_convert/convert_decimal.cpp
        src/ast/numeric_convert/convert_based.cpp

        src/analyze/check/label_match.cpp
        src/analyze/syntax.cpp

        src/context.cpp
        src/diagnostic_handler.cpp
        src/diagnostic_printer.cpp

        src/parser/error_handler.cpp
        src/parser/position_cache.cpp
        src/parser/grammar.cpp  # ---- memory exhausting ----
        src/parser/parse.cpp
)


if(DEVELOPER_BOOST_SPIRIT_X3_DEBUG)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG
    )
endif()


# Maybe Solution - use [Object Libraries](https://cmake.org/cmake/help/latest/command/add_library.html#object-libraries)
# to compile only {grammar,parse}.cpp with high memory requirements options
set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_10240MiB
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    SYSTEM PUBLIC
        $<INSTALL_INTERFACE:include>
)


## Fix for Warning 'declaration of "symbol" hides previous local declaration' - too much changes 
# required to fix it ...
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_source_files_properties(
        # ... due to nested std::string_view const {symbol, node_typename}
        src/ast/ast_printer.cpp
        src/ast/ast_stats.cpp
        PROPERTIES
            COMPILE_FLAGS
                /wd4456 # C4456 - declaration of 'identifier' hides previous local declaration
    )
endif()


##
# Clang -Weverything
#
# Disable some warnings.
#
#   "-Wno-switch-default":
#     If one extended an *enum*, you'd fall into the default case which probably
#     isn't what you want. The correct thing to do is to remove the default case
#     and get warnings for unhandled conditions, see
#     [Why does Clang/LLVM warn me about using default in a switch statement where all enumerated cases are covered?](
#     https://softwareengineering.stackexchange.com/questions/179269/why-does-clang-llvm-warn-me-about-using-default-in-a-switch-statement-where-all)
#     See also compiler test case [godbolt.org](https://godbolt.org/z/7hGecT6qx)
if(COMPILER_CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        set_source_files_properties(
            src/ast/ast_formatter.cpp
            PROPERTIES
                COMPILE_FLAGS
                    -Wno-switch-default
        )

        set_source_files_properties(
            src/parser/grammar.cpp
            PROPERTIES
                COMPILE_FLAGS
                    -Wno-disabled-macro-expansion
                    -Wno-global-constructors
                    -Wno-exit-time-destructors
        )
    endif()
endif()
