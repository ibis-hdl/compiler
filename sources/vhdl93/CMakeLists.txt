## EDA/VHDL93 project
project(vhdl93 LANGUAGES CXX)

set(PROJECT_LIB vhdl93_grammar)

set(LIB_SOURCES
    src/ast/based_literal.cpp
    src/ast/decimal_literal.cpp
    src/grammar.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

add_library(${PROJECT_LIB} STATIC ${LIB_SOURCES})

#target_include_directories (${PROJECT_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#add_dependencies(${PROJECT_LIB} boost-spirit-x3)
add_dependencies(${PROJECT_LIB} gsl)

set_target_properties(${PROJECT_LIB} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_LIB} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_LIB} PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(${PROJECT_LIB} PRIVATE -Wall -Wextra)

# test suite
add_subdirectory(test)
