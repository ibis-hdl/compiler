################################################################################
# scratchpad projects
################################################################################

project(playground)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

#add_executable(x3_string_literal            x3_string_literal.cpp)
#add_executable(x3_string_literal_minimal    x3_string_literal_minimal.cpp)
add_executable(x3_string_literal_attr       x3_string_literal_attr.cpp)

add_executable(x3_integer                   x3_integer.cpp)
