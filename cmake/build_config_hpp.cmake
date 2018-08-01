## Compiler Features required for common/utils
include(CheckCXXCompilerFlag)


check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}
" EDA_HAVE_BUILTIN_UNREACHABLE)


check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}
" EDA_HAVE_BUILTIN_EXPECT)


# MinGW doesn't seems to have C++11 std::quick_exit()
check_cxx_source_compiles("
#include <cstdlib>
int main() {
    std::quick_exit(EXIT_FAILURE);
    return 0;
}
" EDA_HAVE_STD_QUICK_EXIT)


# The plattform/compiler checks belongs to eda::common
configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/util/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/util/compiler_support.hpp"
)
