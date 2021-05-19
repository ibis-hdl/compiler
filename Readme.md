IBIS HDL project
================

## Build

### Required Tools to Build & Configuration

* C++17 compliant compiler, tested with
    - clang++ 11 (in 2021), g++10 untested
    - g++ 7.3.0 Windows MinGW (in 2018)
    - Visual Studio 2017, Version 15.8 (in 2018)

* cmake 3.18
    - ninja (recommended)
    - GNU make (not well supported by maintainer)

* python 3 to generate some files

* lot of memory, highly recommended more than 16GB


### Required 3rd party Libraries

* Boost 1.73
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)

The following libraries are downloaded automatically into project's external
directory from git repositories:

* CLI11
* GLS (currently unused)


#### Compiling Boost Libs on Windows

You may come across to build Boost libs by yourself - create a batch file.

For Clang-Win:

```
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64

rem link: legal values: "shared" "static"

b2 -j%NUMBER_OF_PROCESSORS% ^
--stage-libdir=lib64-clang-11.0.0 ^
link=shared ^
toolset=clang-win address-model=64 architecture=x86 stage ^
--with-filesystem --with-locale --with-stacktrace --with-system --with-test --with-thread
```

and for C++17 capable MS Visual Studio 14.1:

```
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x64

rem link: legal values: "shared" "static"

b2 -j%NUMBER_OF_PROCESSORS% ^
--stage-libdir=lib64-msvc-14.1 ^
link=shared ^
toolset=msvc address-model=64 architecture=x86 stage ^
--with-filesystem --with-locale --with-stacktrace --with-system --with-test --with-thread
```


### Running tests

```
env CTEST_OUTPUT_ON_FAILURE=1 make check
ctest --verbose

### verbose build
ninja -v

### ninja single core build
ninja -j1
```

Testing hints (verbose flags '-VV'):

```
# list all test
$ ctest -N
# run all test and show output on errors
$ ctest --output-on-failure
# run specific test <test>
$ ctest -R <test>
# run specific test <test> and show output on errors
$ ctest --output-on-failure -R <test>
```


Developer
---------

### Intro

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

**More serious**: The source code has partially documentation which is
expressive, but outdated. A documentation marathon is required if the
source base is stable.

### Clang Tidy

#### Disabled checks, which shouldn't - FixMe

- [misc-no-recursion](https://clang.llvm.org/extra/clang-tidy/checks/misc-no-recursion.html):
  *Until the ast_printer recursive call chain has been solved.*

- [cert-err58-cpp](https://clang.llvm.org/extra/clang-tidy/checks/cert-err58-cpp.html):
  *It's correct, but depend on others libraries.*

- [cppcoreguidelines-pro-bounds-array-to-pointer-decay](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay.html):
  *Ignored at this time. With C++20 with get [std::span](https://en.cppreference.com/w/cpp/container/span)
   aka gsl::span aka gsl:: gsl::array_view. Also starting with C++20 we has also
   [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location) which allows to write assert macros with C++20.*

- [bugprone-branch-clone](https://clang.llvm.org/extra/clang-tidy/checks/bugprone-branch-clone.html):
  *This check ignores the C++ `[[fallthrough]]` attribute specifier, hence twice the source annotations.* But it
  checks and examines conditional operators, so we can't it disable completely. Hopefully later Clang-tidy
  version will honor those attribute specifier.

- [readability-identifier-naming](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
  *Here a lot of effort is required to consolidate and unify all the naming*, e.g. see
  [.clang-tidy](https://github.com/xournalpp/xournalpp/blob/master/.clang-tidy) or
  [.clang-tidy](https://github.com/ROCmSoftwarePlatform/AMDMIGraphX/blob/develop/.clang-tidy) as example.

#### Permanently disabled checks

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):
  *This transformation is purely stylistic. We are not quite that modern.*

- [readability-magic-numbers](https://clang.llvm.org/extra/clang-tidy/checks/readability-magic-numbers.html), cppcoreguidelines-avoid-magic-numbers:
  *This goes too far to force this everywhere.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):
  *This is correct, but is used here for classification purposes.*

- [cppcoreguidelines-pro-type-vararg](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-type-vararg.html):
  *By using Boost UTF this rule is triggered on each BOOST_TEST macros. No c-style vararg functions are written in this project.*


## ToDo


Obviously the intend is to get the parser working and hence the
project.


### Boost.Spirit X3 Notes

**WARNING:** Notes about parser rule definition

There are some 'anonymous' helper rules (to break down the complexity and
to enforce the attributes required) used in the specific rule's detail
namespace. The X3 tags the rules, e.g.:

```
  auto const rule = x3::rule<struct _, ...> { "..." } = ...
```

It would be naturally to use the parent rules's tag type which belongs the
detail helper. But, unfortunately the memory consumption increases dramatically
(8+8)GB RAM/SWAP isn't enough). Following StackOverflow
[X3: Linker Error (unresolved external symbol “parse_rule”) on nonterminal parser](
  https://stackoverflow.com/questions/50277979/x3-linker-error-unresolved-external-symbol-parse-rule-on-nonterminal-parser?answertab=active#tab-top)
Sehe's notes, re-using the tag type is recipe for disaster. The rule tags are
what dispatches the implementation function in the case of
separated compilation units.

- Fix Testcase attribute_specification, unit test failed seriously with:

```
unknown location(0): fatal error: in "parser_rule/attribute_specification/_1": class std::bad_alloc: bad allocation
../testsuite/vhdl/parser_rules/src/test/attribute_specification_test.cpp(46): last checkpoint
```

- Add TestCase for assertion_statement, assertion self is tested already. It appends only
  "label: .... ;" to the tests.

- testsuite's testing_parser may setup on error a message with "Unparsed input left ...",
  which goes to the parser::error_handler, which renders this as "Parse ERROR: ..."
  This isn't the error message intended to display. Note: changing this results into
  failed failure tests due to changes messages!

- Make Tests to check expectation points for ';'

- Check [**Splitting Boost.Spirit.X3 parsers into several TUs**](
  https://stackoverflow.com/questions/59709229/splitting-boost-spirit-x3-parsers-into-several-tus)

- Check [Trying to convert a VHDL BNF to a labeled BNF for BNFC](
  https://stackoverflow.com/questions/44166199/trying-to-convert-a-vhdl-bnf-to-a-labeled-bnf-for-bnfc)

- Maybe a compiler template firewall must be introduced, see
  [Internal compiler error, while using boost spirit x3](
   https://stackoverflow.com/questions/40195894/internal-compiler-error-while-using-boost-spirit-x3).

### Fix Parser Testsuite

The tests passed in 2018, using Boost v1.68's spirit X3. Only problems mentioned
in VHDL parser_rules (former) *test_case_FixMe.txt* where known:

  - alias_declaration_00{1...5}
  - entity_aspect/entity_aspect_002.input
  - type_declaration_failure/*
  - interface_constant_declaration/interface_constant_declaration_006.input
  - type_conversion/type_conversion_001.input
  - wait_statement/wait_statement_00x.input
  - binding_indication/binding_indication_00{0,1}.input entity name rule (is work.foo -> name)
  - allocator_003 (http://vhdl.renerta.com/source/vhd00004.htm)
  - component_configuration_000; configuration_declaration_000,
    architecture_body -> must be: work.foo
    reason is related to rule name, where no selected_name is active!!!

Missing tests:

  - concurrent_procedure_call_statement
  - concurrent_signal_assignment_statement

In 2021 boost is bumped to v1.73 and following *test_vhdl_parser_rule* tests failed:

  - test_case_name = aggregate/aggregate_001;
  - test_case_name = aggregate/aggregate_002;
  - test_case_name = aggregate/aggregate_003;
  - test_case_name = aggregate/aggregate_006;
  - test_case_name = attribute_specification/attribute_specification_001;
  - test_case_name = use_clause/use_clause_000;

It is even reproducible with the code of 2018 (git tag R2018 using Boost v1.68.0) and
switching to Boost v1.73. So these errors are imminent in these code base
before. Anyway, parser is still the main work ground.

But there is more:

- It looks like testsuite/librules/rules_{a-z} instances are not necessary.
  testsuite/librules/rules_api should be able to access grammar.cpp symbols.
  The final question is, does testsuite/librules/rules_{a-z} really need to create
  all instances again?

- testsuite/numeric_convert/numeric_parser again has a helper function parse(),
  just like testsuite/parser_rules/testing_parser !!! Maybe combine them?


### App Logging

There are several needs to log to the user. The VHDL assert and
report messages are obvious. Next are messages of warning and errors
from VHDL compiler self. Further internal and debugging messages,
maybe by use of boost.log or spdlog.

Generally, a lot of information go trough std::cerr without prefix
or even using colorizing. E.g. on stacktrace_{gdb.boost} it's not
clear what comes from what.

### Project structure

- testsuite/util/basic_failure_diagnostic_fixture and testsuite/vhdl/util/failure_diagnostic_fixture
  still BAD NAMING ...

### CMake

- use CMake's Unity Build Mode

- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
  and [Modern CMake Examples](https://github.com/pr0g/cmake-examples)
- [PCH](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html?highlight=pch)
  and [reusing them](https://cmake.org/cmake/help/git-stage/command/target_precompile_headers.html)
- [Unity Build Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE)
  see also [CMake Discourse](https://discourse.cmake.org/t/one-source-to-create-multiple-objects/2819)
- [C++ dependency management with CMake’s FetchContent](https://medium.com/analytics-vidhya/c-dependency-management-with-cmakes-fetchcontent-4ceca4693a5d)

- **Regards to build options, see [Making CMake work for you](
  http://www.stablecoder.ca/2018/10/30/full-cmake-helper-suite.html)**

### Sources

- **FixMe**: Before main's init() there is no text style/color functionality even in the
  stacktrace_{gdb,boost} functions.

- Make position_cache std::string_view aware. The position_cache owns the HDL file
  contents as string, so there is no reason the cope with std::string::iterator
  everywhere. This does influence other code parts apart of position_cache!

- position_cache got interesting warnings by compiling with `-Weverything`
  regards to `.line_number()` and `.get_line_start`: Investigate!

- Simplify formatting output using [fmtlib/fmt](https://github.com/fmtlib/fmt),
  which supports color output; related to C++20 std::format support

- Get clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the '// 'clang-format {off|on}'
  pragmas especially on class members.

- Write git hooks for checking using clang-{tidy,format} et al. Note, that not
  everywhere clang-format may be installed.

- AST printer: move ast_printer into ast_walker, printer breaks down into simple class
  like ast_stats.

  - util::visit_in_place using boost.hana with util::overloaded, afterwards it can
    be removed

  - use for recursive depth counting a class with ctor/dtor increment/decrement
    capabilities - recursive_depth_{counter,guard} - as context i.e.

  -  ast_stats.cpp:
    - ast_stats sort order - use enum sort::{ascending, descending}
    - worker collector{ count_map, untagged_nodes } fix to
      worker stats_worker{ count_map, untagged_nodes };

- we have buildinfo_static.hpp.in, buildinfo.hpp.in using git info and date/time
  would be useful. Copy git part temporary to ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}
  to avoid unnecessary rebuild, for an idea look at blender sources.

- parser's and syntax's error_handler should have the same API with position_proxy
  to unify error_handler and hence his formatter.

- parser's error_handler should also use the vhdl::context to allow multiple parse errors
  from expectation points, e.g. forgotten ';' at the end. Maybe the name of vhdl::context
  isn't appropriate any more than.

- Write a formatter for all error report classes/functions, e.g. parser::error_handler.
  An idea may be [Controlling output of Boost.Test source location format](
  https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format).


### NumericConvert / 2nd pass Parser

The whole conversation of the numerical VHDL types from the AST is confusing,
possibly also complicated:

- warnings pointed:

  ```
  [7/169] Building CXX object testsuite\vhdl\numeric_convert\CMakeFiles\testrunner_vhdl_numeric_convert.dir\src\binary_string.cpp.obj
  ..\testsuite\vhdl\numeric_convert\src\binary_string.cpp(54): warning C4244: "Argument": Konvertierung von "const uint64_t" in "unsigned int", möglicher Datenverlust
  ..\testsuite\vhdl\numeric_convert\src\binary_string.cpp(88): warning C4244: "Argument": Konvertierung von "const uint64_t" in "unsigned int", möglicher Datenverlust
  ..\testsuite\vhdl\numeric_convert\src\binary_string.cpp(115): warning C4244: "Argument": Konvertierung von "const uint64_t" in "unsigned int", möglicher Datenverlust
  [14/169] Building CXX object testsuite\vhdl\numeric_convert\CMakeFiles\testrunner_vhdl_numeric_convert.dir\src\test\bit_string_literal_test.cpp.obj
  D:\My\IBIS\boost_1_76_0\boost/test/tools/fpc_op.hpp(134): warning C4244: "Argument": Konvertierung von "const Rhs" in "const FPT", möglicher Datenverlust
  ```

  A double is used as a "generic universal type"; using a template argument,
  i.e. attribute_type, such warnings are bypassed and it is clearer to read.

- In numeric_convert.cpp a lot of "trickery" is done because of splitting the
  numeric VHDL types into their components by the actual vhdl::parser to save
  parse time. Even with C++20 there are more possibilities, eg.
  [coliru](https://coliru.stacked-crooked.com/a/17f844b879507aed):


  ```
  #include <iostream>
  //#include <ranges> // C++20
  #include <range/v3/view.hpp>
  #include <string_view>
  #include <algorithm>
  #include <iterator>

  template <typename RangeT>
  void print(RangeT str) {
      std::copy(str.begin(), str.end(), std::ostream_iterator<char>(std::cout));
      std::cout << "\n";
  }

  int main()
  {
      using namespace std::literals;
      auto const bits = { "https:"sv, "//"sv, "cppreference"sv, "."sv, "com"sv };
      print(bits | ranges::views::join);
  }

  ```

  ... with this the nested boost::join() can be omitted and this becomes more
  readable. In principle the problem with the '_' in the literals should be
  avoided with std::ranges.

- Next: [Stackoverflow](
  https://stackoverflow.com/questions/29132809/using-boostspiritqi-to-parse-numbers-with-separators?answertab=active#tab-top)
  shows a better approach than the present one.


### Others

- Get a logo, e.g. ibis as mascot with assets sub directories.

- rename all print() member to print_on()

### Testsuite and Boost.Test

- basic_failure_diagnostic_fixture should also save as unified diff, see todo inside header.

- Useful information to store on filesystem are the messages, maybe [Observing test failure messages](
   https://stackoverflow.com/questions/56963902/observing-test-failure-messages/61371602#61371602)

- An interesting feature is described at
  [Controlling output of Boost.Test source location format](
   https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format)


### Documentation

Switch from MarkDown to ReStructuredText. At this state, Doxygen miss some MarkDown
and ReStructuredText features, Sphinx multi projects and doesn't seems to support
Doxygen's Todo tags/list.


Check [LSST DM Developer Guide](https://developer.lsst.io/index.html) for styles
and recommendations.


