################################################################################
## EDA/vhdl project
##
## file: sources/vhdl/CMakeLists.txt
################################################################################

project(eda_vhdl_parser LANGUAGES CXX)


add_library(${PROJECT_NAME} "")
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        eda::common
)


if(EDA_EXTERNAL_BOOST_SPIRIT_X3)
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
        
        src/parser/error_handler.cpp
        src/parser/on_error_base.cpp
        src/parser/grammar.cpp  # ---- memory exhausting @compile time ----
        src/parser/parse.cpp
        
        src/analyze/error_handler.cpp
        src/analyze/check/label_match.cpp
        src/analyze/syntax.cpp
        
        src/context.cpp
)


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


# MSVC and MSYS2/MinGW64 has problems with spirit.x3
# increase object size for windows compiler, otherwise will fail
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set_source_files_properties(
        src/parser/grammar.cpp
        PROPERTIES 
            COMPILE_FLAGS /bigobj
    )
elseif(WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties(
        src/parser/grammar.cpp
        PROPERTIES 
            COMPILE_FLAGS -Wa,-mbig-obj
    )
endif()
    

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:
            # No min/max macros on windows, \see [#define NOMINMAX using std::min/max](
            #  https://stackoverflow.com/questions/13416418/define-nominmax-using-stdmin-max)
            NOMINMAX
            # also remove unnecessary warnings about unchecked iterators
            _SCL_SECURE_NO_WARNINGS        
        >
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
