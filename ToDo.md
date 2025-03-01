# Todo Review 2024/2025

## Issue related

## Urgent
- ClangTidy (cppcoreguidelines-avoid-const-or-ref-data-members) fixes, 
  Warnings are disabled - fixit
- CLangTidy fix [modernize-use-ranges]

- there are a lot of similar dataset.{hpp,cpp}

- rename  <ibis/vhdl/ast.hpp> to  <ibis/vhdl/ast/nodes.hpp>

- DRY ast_printer.cpp - consider std::enumerate AND don't-repeat-yourself!
  ```cpp
    std::size_t const SIZE = vector.size() - 1;
    // NOLINTNEXTLINE(readability-identifier-length)
    for (auto i{ 0UL }; auto const& element : vector) {
        (*this)(element);
        if (i++ != SIZE) {
            os << ",\n";
        }
    }
  ```
  Check [CoLiRu](https://coliru.stacked-crooked.com/a/4f54446323e22e8e) for solution

- unify switch/case handling, e.g.:
	```cpp
	[[unlikely]] case unspecified:
		// probably an unintentionally constructed enum by default
		cxx_bug_fatal("based literal numeric_type *unspecified*!");
	```

- Check add_test(NAME ... WORKING_DIRECTORY ... COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ...)
  regards:
    CMake Warning (dev) at testsuite/frontend/CMakeLists.txt:9 (add_test):
      uninitialized variable 'CMAKE_BUILD_DIR'
    This warning is for project developers.  Use -Wno-dev to suppress it.

    CMake Warning (dev) at testsuite/frontend/CMakeLists.txt:9 (add_test):
      uninitialized variable 'CMAKE_RUNTIME_OUTPUT_DIRECTORY'
    This warning is for project developers.  Use -Wno-dev to suppress it.

- file_mapper.add_file(filename, ...) - make filename of fs::path to ensure proper arguments and 
  function signature. Internally it could make a string/view from this.

## CMake Presets

- check approach cmake-init by friendlyanon, also Standards (https://github.com/ibis-hdl/compiler/community)

- CMake Unity build and (S)CCache with PCH - all together doesn't seems to work well, 
  see [CMake's user preset](cmake\presets\user\Readme.md)

- CMake Dev-Mode für gcc,clang,msvc mit NDEBUG und sanitizer
  [How to enable assert in CMake Release mode?](
   https://stackoverflow.com/questions/22140520/how-to-enable-assert-in-cmake-release-mode)
  [What are CMAKE_BUILD_TYPE: Debug, Release, RelWithDebInfo and MinSizeRel?](
  https://stackoverflow.com/questions/48754619/what-are-cmake-build-type-debug-release-relwithdebinfo-and-minsizerel)

- check 
  - https://martin-fieber.de/blog/cmake-presets/
  - https://github.com/MartinHelmut/cpp-gui-template-sdl2/blob/main/CMakeLists.txt

- PCH and DEVELOPER_MODE looks fragile/wrong, check it 

- https://github.com/friendlyanon/cmake-init-multi-target
- clang-tidy support there?


## CMake CTest

- label ctest: https://stackoverflow.com/questions/24495412/ctest-using-labels-for-different-tests-ctesttestfile-cmake

- Somewhere in testsuite there is a class, which gives more context on failed test 
  cases. Improve it with std:format, header, footer etc to distinguish it from 
  boost.Test generated messages. Maybe check length of strings and format report, so it works for long and short strings.
  Concrete use case is
  -  testsuite/vhdl/grammar/src/test/test_bit_string_literal.cpp(130), which fails 
     only on MSVC in Debug mode.
  - testsuite\vhdl\parser_rules\src\test\abstract_literal_test.cpp e..g, where
    Assertion failed: cannot subtract incompatible string_view iterators. No problem,
    since it will be rewritten.

## Clang Format/Tidy, Clangd

- update
  check https://github.com/ClickHouse/ClickHouse/tree/master for configs

- use Clangd, see https://clangd.llvm.org/design/include-cleaner, https://github.com/ClickHouse/ClickHouse/blob/master/.clangd


## IBIS Compiler Project related

- ast_print has 2x "visit()" overload - one for variant and one for vector, rename them for vector
  to e.g. visit_each() (since nodes are visited inside std::for_each())

- ast_printer - use new formatter for enums, or even replace with ast_walker NG

- ast_walker NG - see H:\work\ibis-CXX\ibis-working-on\use-ast_walker_ng
  Note: Clang -Weverything complains about:
  - cxx_bug_fatal("VHDL BNF rules violation, parser rule failed!");
    warning: empty expression statement has no effect; remove unnecessary ';' to silence this warning [-Wextra-semi-stmt]
  - std::string_view const node_typename{ "expression*" };
    warning: declaration shadows a local variable [-Wshadow]
	Possible Solution: name it "symbol_<node-name>_meta", nested member class
	```cpp
	template <typename NodeT, typename Enable>
	struct symbol_meta_info {
		string_view name;
		size_t node_size = sizeof(<NodeT>);
	};
	```
  check on use of C++23 "deduce this"

- New API file_mapper, position_cache still insufficient, see testing_parser.hpp line 62,
  file id is referred after std::move  

- <ibis/vhdl/context.hpp>  // failure_status is not obvious!

- unify <ibis/vhdl/parser/context.hpp>

- rewrite cxx_debug_assert using variadic args and std::format, cxx_bug_fatal() has no assert(true/false) in message

- rewrite ibis::message, or use libassert 

- numeric NG - see H:\work\ibis-CXX\ibis-working-on\use-x3-playground

- Rework <testsuite/aliases.hpp>

- Clear GH caches and clean Conan's temporaries after build to save storage space
  `conan cache clean -s -b -d -t`

- Write Obsidian C++ Idioms, e.g. "const-and-back-again", non-virtual-interface ...

- Check Clang on Windows, see [Understanding the different flavors of Clang C and C++ compilers in Windows](
  https://blog.conan.io/2022/10/13/Different-flavors-Clang-compiler-Windows.html)
  

- write CMake function as replacement for 
  `set(CMAKE_PROJECT_INCLUDE_BEFORE "${CMAKE_SOURCE_DIR}/cmake/project-meta-info.cmake")` for settings project's vars; a better way might be to do something like:
  ```
  include(read_project_info.cmake)
  read_project_info(metadata.json prefix_)
  ```
  or something, then you can use string(JSON) instead of dealing with cmake code

## ADD to ToDo in the final doc

### test_ast_formatter has problems with MSVC and Debug build

See `test_ast_formatter.cpp` BUG labeled, and [Godbolt.org](https://godbolt.org/z/57YYfx5aj) to reduce/check the issue: 
```
__msvc_string_view.hpp(1058): note: Error was caused by calling an undefined function or an undeclared “constexpr”
```
