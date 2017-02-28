project(vhdl93 LANGUAGES CXX)
message(INFO "cmake'ing <vhdl93>")

set(VHDL93_SOURCES
    grammar.cpp
)

include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

add_executable(vhdl93 ${VHDL93_SOURCES})

add_dependencies(vhdl93 gsl)
add_dependencies(vhdl93 boost-spirit-x3)

set_target_properties(vhdl93 PROPERTIES CXX_STANDARD 14)
set_target_properties(vhdl93 PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(vhdl93 PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(vhdl93 PRIVATE -Wall -Wextra)

target_link_libraries(vhdl93 ${Boost_SYSTEM_LIBRARY})
