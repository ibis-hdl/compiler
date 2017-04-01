cmake_minimum_required(VERSION 3.6)

## EDA/VHDL93 project TestBench
project(test_vhdl93 LANGUAGES CXX)

set(BIN_SOURCES
    app_mock.cpp
    data_set.cpp
    basic_production_rules.cpp
    error_reporting.cpp
    test_vhdl93.cpp
)

add_executable(${PROJECT_NAME} ${BIN_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)


#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} gsl)


## Boost Requirements
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})

add_library(boost-filesystem SHARED IMPORTED)
set_property(TARGET boost-filesystem PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost-filesystem PROPERTY IMPORTED_LOCATION ${Boost_FILESYSTEM_LIBRARY})

add_library(boost-system SHARED IMPORTED)
set_property(TARGET boost-system PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost-system PROPERTY IMPORTED_LOCATION ${Boost_SYSTEM_LIBRARY})



target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl93_grammar
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_test(NAME test_vhdl93_parser
    COMMAND ${PROJECT_NAME} -- ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(x3_debug EXCLUDE_FROM_ALL x3_debug.cpp)
target_link_libraries(x3_debug
    PRIVATE
    eda::vhdl93_grammar
    ${Boost_SYSTEM_LIBRARY}
)
