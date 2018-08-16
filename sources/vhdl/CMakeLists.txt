################################################################################
## sources/vhdl/CMakeLists.txt
################################################################################

################################################################################
## EDA/VHDL project
################################################################################

project(eda_vhdl_parser LANGUAGES CXX)


set(VHDL_PARSER_SOURCE
    src/ast/literal_printer.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    src/ast/ast_printer.cpp
    src/ast/ast_stats.cpp
    src/ast/numeric_convert.cpp
    
    src/parser/error_handler.cpp
    src/parser/on_error_base.cpp
    src/parser/grammar.cpp
    src/parser/parse.cpp
    
    src/analyze/error_handler.cpp
    src/analyze/check/label_match.cpp
    src/analyze/syntax.cpp
    
    src/context.cpp
)

add_library(${PROJECT_NAME} STATIC ${VHDL_PARSER_SOURCE})
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})

# Ninja Build
set_property(TARGET eda_vhdl_parser PROPERTY JOB_POOL_COMPILE job_pool_max_cores)
set_property(TARGET ${PROJECT_NAME} PROPERTY JOB_POOL_LINK    job_pool_one_core)


target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall 
    -Wextra
)


if(CLANG_WARN_EVERYTHING)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE
            -Weverything
            -Wno-c++98-compat -Wno-c++98-compat-pedantic
            # FixMe: Optimize AST nodes for size
            -Wno-padded
        )
    
        set_source_files_properties(
            src/ast/literal_printer.cpp 
            src/ast/keyword_token.cpp
            src/ast/operator_token.cpp
            PROPERTIES COMPILE_FLAGS 
                -Wno-covered-switch-default
        )
        
        set_source_files_properties(
            src/parser/grammar.cpp
            PROPERTIES COMPILE_FLAGS 
                "-Wno-disabled-macro-expansion -Wno-global-constructors -Wno-exit-time-destructors"
        )
    endif()
endif(CLANG_WARN_EVERYTHING)


# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=1024)
endif()


## Boost.Org 
# Spirit X3 is required for the parser - we are working on developer branch. 
# Nevertheless Spirit self depends on other headers, e..g boost.range
find_package(Boost)

# depend on newer Spirit.X3 versions
add_dependencies(${PROJECT_NAME} boost-spirit-x3)

# Boost.Org depend includes
include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})


# Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)


## doc, etc.
add_subdirectory(doc)

