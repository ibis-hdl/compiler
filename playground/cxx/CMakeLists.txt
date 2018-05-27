################################################################################
## playground/cxx/CMakeLists.txt
################################################################################

################################################################################
# C++ scratchpad projects
################################################################################

project(cxx_playground)


add_executable(cxx_ellipsis_compress         EXCLUDE_FROM_ALL cxx_ellipsis_compress.cpp)
add_executable(cxx_variant_print_visitor_concept EXCLUDE_FROM_ALL cxx_variant_print_visitor_concept.cpp)
add_executable(cxx_indent_ostreambuf         EXCLUDE_FROM_ALL cxx_indent_ostreambuf.cpp)
add_executable(cxx_pow_constexpr             EXCLUDE_FROM_ALL cxx_pow_constexpr.cpp)
add_executable(cxx_string_view_range         EXCLUDE_FROM_ALL cxx_string_view_range.cpp)
