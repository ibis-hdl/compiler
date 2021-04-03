################################################################################
## EDA/vhdl project
##
## file: source/vhdl/CMakeLists.txt
################################################################################

project(eda_vhdl_parser LANGUAGES CXX)


add_library(${PROJECT_NAME})
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        eda::common
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
        src/ast/position_cache.cpp
        src/ast/pretty_node_name.cpp

        src/analyze/error_handler.cpp
        src/analyze/check/label_match.cpp
        src/analyze/syntax.cpp

        src/context.cpp

        src/parser/error_handler.cpp
        src/parser/on_error_base.cpp
        src/parser/grammar.cpp  # ---- memory exhausting @compile time ----
        src/parser/parse.cpp    # FixMe: also creates Grammar instance? Shouldn't!
)

##
# Ninja Build override to cope on low memory situations to compile "big" files
cmake_host_system_information(
    RESULT localhost_RAM_MiB
    QUERY  AVAILABLE_PHYSICAL_MEMORY
)
message(STATUS "Host has ${localhost_RAM_MiB} MiB available physical memory to build.")
# to compile grammar.cpp ~10GB RAM are required using Clang-Win, so 12GiB is set as limit
# GiB = 2^30, MiB = 2^20 Bytes, hence 12*2^(30-20) = 12288 MiB
if(localhost_RAM_MiB LESS 12288)
    # probably to loose on this file, anyway ...
    set_source_files_properties(src/parser/grammar.cpp src/parser/parse.cpp
        PROPERTIES
            JOB_POOL_COMPILE NINJA_JOBS_ONE_CPU
    )
    set_source_files_properties(src/parser/grammar.cpp src/parser/parse.cpp
        PROPERTIES
            COMPILE_FLAGS "-O0 -ftemplate-backtrace-limit=10 -ftemplate-depth=900"
)
endif()


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eda/vhdl/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/eda/vhdl/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_SPIRIT_X3_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)


# handle problems with Spirit.X template depth
target_compile_options(${PROJECT_NAME}
    PRIVATE
        # - limit gcc/clang template error depth printing
        # - increase limit especially for clang recursive template instantiation,
        #   otherwise exceedes maximum depth of 512
        $<$<CXX_COMPILER_ID:GNU>:  -ftemplate-backtrace-limit=0 -ftemplate-depth=1024>
        $<$<CXX_COMPILER_ID:Clang>:-ftemplate-backtrace-limit=0 -ftemplate-depth=1024>
)


##
# Clang -Weverything
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
