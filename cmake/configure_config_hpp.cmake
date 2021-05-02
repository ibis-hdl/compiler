## -----------------------------------------------------------------------------
## Compiler Features required for common/utils
##  -----------------------------------------------------------------------------

include(CheckCXXCompilerFlag)

##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}
" IBIS_HAVE_BUILTIN_EXPECT)


##
# MSVC extension
check_cxx_source_compiles("
#include <cstddef>
int main() {
    int x = 3;
    __assume(x == 3);
    return 0;
}
" IBIS_HAVE_BUILTIN_ASSUME)


##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}
" IBIS_HAVE_BUILTIN_UNREACHABLE)


##
# Pre C++20 support for std::source_location
check_cxx_source_compiles("
#include <experimental/source_location>
int main() {
  std::experimental::source_location location{ std::experimental::source_location::current() };
  return 0;
}
" IBIS_HAVE_EXPERIMENTAL_SOURCE_LOCATION)


# The plattform/compiler checks belongs to eda::common
configure_file(
  "${PROJECT_SOURCE_DIR}/include/ibis/compiler/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include/ibis/compiler/compiler_support.hpp"
)
