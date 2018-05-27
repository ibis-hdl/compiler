################################################################################
## playground/vhdl93/CMakeLists.txt
################################################################################

################################################################################
# VHDL93/Spirit.X3 scratchpad projects
################################################################################

project(vhdl_playground)


add_executable(x3_string_literal_minimal    EXCLUDE_FROM_ALL x3_string_literal_minimal.cpp)
add_executable(x3_string_literal_attr       EXCLUDE_FROM_ALL x3_string_literal_attr.cpp)
add_executable(x3_string_literal_view       EXCLUDE_FROM_ALL x3_string_literal_view.cpp)

add_executable(x3_integer                   EXCLUDE_FROM_ALL x3_integer.cpp)
add_executable(x3_based_literal             EXCLUDE_FROM_ALL x3_based_literal.cpp)
add_executable(x3_based_literal_minimal     EXCLUDE_FROM_ALL x3_based_literal_minimal.cpp)
add_executable(x3_decimal_literal           EXCLUDE_FROM_ALL x3_decimal_literal.cpp)
add_executable(x3_extended_identifier       EXCLUDE_FROM_ALL x3_extended_identifier.cpp)
add_executable(x3_literal                   EXCLUDE_FROM_ALL x3_literal.cpp)
add_executable(x3_expression                EXCLUDE_FROM_ALL x3_expression.cpp)
add_executable(x3_simple_expr               EXCLUDE_FROM_ALL x3_simple_expr.cpp)
add_executable(x3_list_chunk                EXCLUDE_FROM_ALL x3_list_chunk.cpp)
add_executable(x3_integer_solution          EXCLUDE_FROM_ALL x3_integer_solution.cpp)
add_executable(x3_integer_lambda_solution   EXCLUDE_FROM_ALL x3_integer_lambda_solution.cpp)

add_executable(vhdl_numeric_literals        EXCLUDE_FROM_ALL vhdl_numeric_literals.cpp)
target_include_directories(vhdl_numeric_literals PRIVATE 
    ${EDA_BINARY_ROOT_DIR}/external/src/boost-spirit-x3/include
    ${Boost_INCLUDE_DIR}
)

add_executable(x3_ir1045                    EXCLUDE_FROM_ALL x3_ir1045.cpp)
target_include_directories(x3_ir1045 PRIVATE # requires > 1.64
    ${EDA_BINARY_ROOT_DIR}/external/src/boost-spirit-x3/include
)

add_executable(x3_variant_inheritance       EXCLUDE_FROM_ALL x3_variant_inheritance.cpp)


add_executable(vhdl_based_literal           EXCLUDE_FROM_ALL vhdl_based_literal.cpp)


find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(vhdl_expression_eval         EXCLUDE_FROM_ALL vhdl_expression_eval.cpp)
target_link_libraries(vhdl_expression_eval
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl93_grammar?
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)
