## Compiler Features required for common/utils
include(CheckCXXCompilerFlag)

##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}
" EDA_HAVE_BUILTIN_UNREACHABLE)


##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}
" EDA_HAVE_BUILTIN_EXPECT)


##
# MSVC extension
check_cxx_source_compiles("
#include <cstddef>
int main() {
    int x = 3;
    __assume(x == 3);
    return 0;
}
" EDA_HAVE_BUILTIN_ASSUME)


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
  "${PROJECT_SOURCE_DIR}/include/eda/compiler/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/compiler/compiler_support.hpp"
)

# ... also the user configuration 
configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/configuration.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/configuration.hpp"
)
