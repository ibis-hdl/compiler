Developer
=========

Generally honor:

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

**More serious**: The source code has partially doxygen documentation which is
partially expressive, but outdated. A documentation marathon is required if the
source base is **stable**.

## Clang Tidy

There is a CMake target to run Clang-Tidy checks, nevertheless the VS Code extension.
Further the [.clang-tidy](../.clang-tidy) config file applies some checks and disabled others.

### Disabled checks:

There are disabled checks which shouldn't be. Enabling this checks requires more effort:

- [misc-no-recursion](https://clang.llvm.org/extra/clang-tidy/checks/misc-no-recursion.html):
  *Until the ast_printer recursive call chain has been solved.*

- [cert-err58-cpp](https://clang.llvm.org/extra/clang-tidy/checks/cert-err58-cpp.html):
  *It's correct, but depend on others libraries.*

- [cppcoreguidelines-pro-bounds-array-to-pointer-decay](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay.html):
  *Ignored at this time. With C++20 with get [std::span](https://en.cppreference.com/w/cpp/container/span)
   aka gsl::span aka gsl:: gsl::array_view.*

- [bugprone-branch-clone](https://clang.llvm.org/extra/clang-tidy/checks/bugprone-branch-clone.html):
  *This check ignores the C++ `[[fallthrough]]` attribute specifier, hence twice the source annotations.* But it  checks and examines conditional operators, so we can't
  it disable completely. Hopefully later Clang-tidy version will honor those
  attribute specifier.

- [readability-identifier-naming](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
  *Here a lot of effort is required to consolidate and unify all the naming*, e.g. see
  [.clang-tidy](https://github.com/xournalpp/xournalpp/blob/master/.clang-tidy) or
  [.clang-tidy](https://github.com/ROCmSoftwarePlatform/AMDMIGraphX/blob/develop/.clang-tidy) as example.

### Permanently disabled checks:

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):
  *This transformation is purely stylistic. We are not quite that modern.*

- [modernize-use-nodiscard](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-nodiscard.html):
  *This would affect a lot of value returning member functions everywhere and doesn't give any additional information.*

- [readability-magic-numbers](https://clang.llvm.org/extra/clang-tidy/checks/readability-magic-numbers.html), cppcoreguidelines-avoid-magic-numbers:
  *This goes too far to force this everywhere.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):
  *This is correct, but is used here for classification purposes.*

- [cppcoreguidelines-pro-type-vararg](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-type-vararg.html):
  *By using Boost UTF this rule is triggered on each BOOST_TEST macros. No c-style vararg functions are written in this project.*

## Clang-Format

The source format is given by Clang-Format's configuration [.clang-format](../.clang-format), or
even simpler by [EditorConfig](https://editorconfig.org/)'s [.editorconfig](../.editorconfig).

To format source, the CMake target `fix-format` exist, using [TheLartians/Format.cmake](
https://github.com/TheLartians/Format.cmake). Note, formatting `CMakeLists.txt` is excluded.