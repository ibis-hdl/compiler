################################################################################
# scratchpad projects
################################################################################

project(vhdl_playground)


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

add_executable(x3_string_literal             EXCLUDE_FROM_ALL x3_string_literal.cpp)
add_executable(x3_string_literal_minimal     EXCLUDE_FROM_ALL x3_string_literal_minimal.cpp)
add_executable(x3_string_literal_attr        EXCLUDE_FROM_ALL x3_string_literal_attr.cpp)

add_executable(x3_integer                    EXCLUDE_FROM_ALL x3_integer.cpp)
add_executable(x3_based_literal              EXCLUDE_FROM_ALL x3_based_literal.cpp)
add_executable(x3_based_literal_minimal      EXCLUDE_FROM_ALL x3_based_literal_minimal.cpp)
add_executable(x3_decimal_literal            EXCLUDE_FROM_ALL x3_decimal_literal.cpp)
add_executable(x3_literal                    EXCLUDE_FROM_ALL x3_literal.cpp)

add_executable(ellipsis_compress             EXCLUDE_FROM_ALL ellipsis_compress.cpp)

