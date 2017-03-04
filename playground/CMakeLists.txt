################################################################################
# scratchpad projects
################################################################################


################################################################################
## x3_stringview_quoted_string
add_executable(hello ${PROJECT_SOURCE_DIR}/src/x3_stringview_quoted_string.cpp)
add_dependencies(hello gsl)
add_dependencies(hello boost-spirit-x3)

set_target_properties(hello PROPERTIES CXX_STANDARD 14)
set_target_properties(hello PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(hello PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(hello PRIVATE -Wall -Wextra)


################################################################################
## vhdl entity parser

add_executable(vhdl_entity_parser ${CMAKE_CURRENT_SOURCE_DIR}/vhdl_entity_parser.cpp)
add_dependencies(vhdl_entity_parser gsl)
add_dependencies(vhdl_entity_parser boost-spirit-x3)

set_target_properties(vhdl_entity_parser PROPERTIES CXX_STANDARD 14)
set_target_properties(vhdl_entity_parser PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(vhdl_entity_parser PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(vhdl_entity_parser PRIVATE -Wall -Wextra)
