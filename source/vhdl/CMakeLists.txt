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


if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} boost-spirit-x3)
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
        src/parser/grammar.cpp  # ---- memory exhausting @compile time ----
        src/parser/parse.cpp
)


# Maybe Solution - use [Object Libraries](https://cmake.org/cmake/help/latest/command/add_library.html#object-libraries)
# to compile only {grammar,parse}.cpp with high memory requirements options
set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_10240MiB
)


if (IBIS_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ibis/vhdl/detail/pch.hpp>
            #$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ibis/vhdl/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_SPIRIT_X3_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)


##
# Clang -Weverything
#
# FixMe: What was the intent of this disabled warnings?
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
