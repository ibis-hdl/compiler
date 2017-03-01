## EDA/VHDL93 project TestBemch
project(test_vhdl93 LANGUAGES CXX)

set(PROJECT_BIN test_vhdl93)
set(PROJECT_LIB vhdl93_api)

## lib
set(LIB_SOURCES
    grammar_api.cpp
)

add_library(${PROJECT_LIB} STATIC ${LIB_SOURCES})
target_include_directories (${PROJECT_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

## bin
set(BIN_SOURCES
    basic_production_rules.cpp
    test_vhdl93.cpp
)

add_executable(${PROJECT_BIN} ${BIN_SOURCES})

add_dependencies(${PROJECT_BIN} boost-spirit-x3)
add_dependencies(${PROJECT_BIN} gsl)

set_target_properties(${PROJECT_BIN} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_BIN} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_BIN} PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(${PROJECT_BIN} PRIVATE -Wall -Wextra)

target_link_libraries(${PROJECT_BIN} 
    PRIVATE
    ${PROJECT_LIB}
    vhdl93_grammar
    ${Boost_SYSTEM_LIBRARY}
)
