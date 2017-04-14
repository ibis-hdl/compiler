################################################################################
# scratchpad projects
################################################################################

project(vhdl_playground)


add_executable(x3_string_literal_minimal     EXCLUDE_FROM_ALL x3_string_literal_minimal.cpp)
add_executable(x3_string_literal_attr        EXCLUDE_FROM_ALL x3_string_literal_attr.cpp)
add_executable(x3_string_literal_view        EXCLUDE_FROM_ALL x3_string_literal_view.cpp)

add_executable(x3_integer                    EXCLUDE_FROM_ALL x3_integer.cpp)
add_executable(x3_based_literal              EXCLUDE_FROM_ALL x3_based_literal.cpp)
add_executable(x3_based_literal_minimal      EXCLUDE_FROM_ALL x3_based_literal_minimal.cpp)
add_executable(x3_decimal_literal            EXCLUDE_FROM_ALL x3_decimal_literal.cpp)
add_executable(x3_extended_identifier        EXCLUDE_FROM_ALL x3_extended_identifier.cpp)
add_executable(x3_literal                    EXCLUDE_FROM_ALL x3_literal.cpp)

add_executable(ellipsis_compress             EXCLUDE_FROM_ALL ellipsis_compress.cpp)

add_executable(cxx_variant_print_visitor_concept EXCLUDE_FROM_ALL cxx_variant_print_visitor_concept.cpp)

