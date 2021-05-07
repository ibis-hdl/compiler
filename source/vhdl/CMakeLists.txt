################################################################################
## IBIS/vhdl project
##
## file: source/vhdl/CMakeLists.txt
################################################################################

project(ibis_vhdl LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(ibis::vhdl ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ibis::common
)


if(DEVELOPER_EXTERNAL_BOOST_SPIRIT)
    add_dependencies(${PROJECT_NAME} external-boost-spirit)
endif()


target_sources(${PROJECT_NAME}
    PRIVATE
        src/ast/literal_printer.cpp
        src/ast/keyword_token.cpp
        src/ast/operator_token.cpp
        src/ast/ast_printer.cpp
        src/ast/ast_stats.cpp
        src/ast/numeric_convert.cpp
        src/ast/pretty_node_name.cpp

        src/analyze/error_handler.cpp
        src/analyze/check/label_match.cpp
        src/analyze/syntax.cpp

        src/context.cpp

        src/parser/error_handler.cpp
        src/parser/on_error_base.cpp
        src/parser/position_cache.cpp
        src/parser/grammar.cpp  # ---- memory exhausting ----
        src/parser/parse.cpp
)


# Maybe Solution - use [Object Libraries](https://cmake.org/cmake/help/latest/command/add_library.html#object-libraries)
# to compile only {grammar,parse}.cpp with high memory requirements options
set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_10240MiB
)


if(${PROJECT_NAME}_PCH)
    # override ibis::pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/ibis/vhdl/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/ibis/vhdl/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis::pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_SPIRIT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)


##
# Clang -Weverything
#
# Disable some warning which aren't relevant here.
#
# * -Wno-covered-switch-default
#   - if one extended the enum, you'd fall into the default case which probably
#     isn't what you want. The correct thing to do is to remove the default case
#     and get warnings for unhandled conditions, see
#     [Why does Clang/LLVM warn me about using default in a switch statement where all enumerated cases are covered?](
#     https://softwareengineering.stackexchange.com/questions/179269/why-does-clang-llvm-warn-me-about-using-default-in-a-switch-statement-where-all)
#   - in project, default branches are covered with `cxx_unreachable_bug_triggered();`
#     normally
if(COMPILER_CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

        set_source_files_properties(
            src/ast/literal_printer.cpp
            src/ast/keyword_token.cpp
            src/ast/operator_token.cpp
            PROPERTIES
                COMPILE_FLAGS
                    -Wno-covered-switch-default
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
