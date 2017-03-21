## EDA/VHDL93 project TestBemch
project(test_vhdl93 LANGUAGES CXX)

set(BIN_SOURCES
    basic_production_rules.cpp
    error_reporting.cpp
    test_vhdl93.cpp
    
)

add_executable(${PROJECT_NAME} ${BIN_SOURCES})

#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
add_dependencies(${PROJECT_NAME} gsl)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
    vhdl93_grammar
    ${Boost_SYSTEM_LIBRARY}
)

add_test(test_vhdl93 ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME})
