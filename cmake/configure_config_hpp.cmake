## Compiler Features required for common/utils
include(CheckCXXCompilerFlag)

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


##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}
" EDA_HAVE_BUILTIN_UNREACHABLE)


# The plattform/compiler checks belongs to eda::common
configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/compiler/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/compiler/compiler_support.hpp"
)

# ... also the user configuration
# FixMe: Should be build_configuration.hpp, or even use target_compile_definitions
# for the files affected. So its to global here for the use of.
configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/configuration.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/configuration.hpp"
)
