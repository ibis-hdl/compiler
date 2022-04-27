IBIS HDL project
================

## Build

### Build on Windows

Until 2021 the main developer machine was Fedora/Linux. In 2022 I started with developing on Windows, using WSL2 and container, also VS Code.

Open *Visual Studio 2022 Developer Command Prompt* to get the tool chain correct
initialized.

The best to continue is to install [Python's virtual environment](https://docs.python.org/3/library/venv.html):

```
python -m venv .venv
```

If you run it from PowerShell, you have to prepare it, see 
[here](https://stackoverflow.com/questions/1365081/virtualenv-in-powershell):

```
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force
./.venv/Scripts/activate.ps1
pip install conan
```

install [conan](https://conan.io/) as prerequisite, than you can start to build:

```
cmake --list-presets=all
...
cmake --preset "windows-msvc-release"
...
cmake build --preset "windows-msvc-release"
...
```

### Build on Linux

You know what to do :)

### Required Tools to Build & Configuration

* C++20 compliant compiler, have developed and tested with
    - Visual Studio 2022 Developer Command Prompt v17.1.6
    - clang++ 13
    - g++ 12

* CMake 3.20
    - ninja 1.10.2

* python 3 to generate some files

* lot of memory, highly recommended more than 16GB


### Required 3rd party Libraries

* [Boost](https://www.boost.org/) 1.78
    - system
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [strong_type](https://github.com/rollbear/strong_type)

By using [Conan package manager for C and C++](https://github.com/conan-io/conan)
with [CMake wrapper](https://github.com/conan-io/cmake-conan) the libraries are
build within the project.

## Developer

### Intro

Generally honor:

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

**More serious**: The source code has partially documentation which is
expressive, but outdated. A documentation marathon is required if the
source base is stable.

### Clang Tidy

The is a CMake target to run Clang-Tidy checks, nevertheless the VS Code extension.

#### Disabled checks:

There are disabled checks which shouldn't be. Enabling this checks requires more effort:

- [misc-no-recursion](https://clang.llvm.org/extra/clang-tidy/checks/misc-no-recursion.html):
  *Until the ast_printer recursive call chain has been solved.*

- [cert-err58-cpp](https://clang.llvm.org/extra/clang-tidy/checks/cert-err58-cpp.html):
  *It's correct, but depend on others libraries.*

- [cppcoreguidelines-pro-bounds-array-to-pointer-decay](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay.html):
  *Ignored at this time. With C++20 with get [std::span](https://en.cppreference.com/w/cpp/container/span)
   aka gsl::span aka gsl:: gsl::array_view.*

- [bugprone-branch-clone](https://clang.llvm.org/extra/clang-tidy/checks/bugprone-branch-clone.html):
  *This check ignores the C++ `[[fallthrough]]` attribute specifier, hence twice the source annotations.* But it
  checks and examines conditional operators, so we can't it disable completely. Hopefully later Clang-tidy
  version will honor those attribute specifier.

- [readability-identifier-naming](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
  *Here a lot of effort is required to consolidate and unify all the naming*, e.g. see
  [.clang-tidy](https://github.com/xournalpp/xournalpp/blob/master/.clang-tidy) or
  [.clang-tidy](https://github.com/ROCmSoftwarePlatform/AMDMIGraphX/blob/develop/.clang-tidy) as example.

#### Permanently disabled checks:

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


## ToDo


Obviously the intend is to get the parser working and hence the
project. Even the compiler requires C++20, the tools inside [Microsofts Devcontainer](https://github.com/Microsoft/vscode-dev-containers) are not
the latest, hence still sticking with C++17 (e.g. C++20 std::source_location
and others).


### Boost.Spirit X3 Notes

The X3 rules are from start of the project in 2017, so `grammar_def.h` requires
rework. The headers are generated from EBNF using a python script. Only recursive
rules require the template engine of BOOST_SPIRIT_{DECLARE, DEFINE}.

- There are some 'anonymous' helper rules (to break down the complexity and
  to enforce the attributes required) used in the specific rule's detail
  namespace. The X3 tags the rules, e.g.:

  ```
    auto const rule = x3::rule<struct _, ...> { "..." } = ...
  ```

  It would be naturally to use the parent rules's tag type which belongs the
  detail helper. Following StackOverflow
  [X3: Linker Error (unresolved external symbol “parse_rule”) on nonterminal parser](
  https://stackoverflow.com/questions/50277979/x3-linker-error-unresolved-external-symbol-parse-rule-on-nonterminal-parser?answertab=active#tab-top) at
  Sehe's notes, re-using the tag type is recipe for disaster. The rule tags are
  what dispatches the implementation function in the case of
  separated compilation units.

- Fix Testcase attribute_specification, unit test failed severe (not reproducible) with:

  ```
  unknown location(0): fatal error: in "parser_rule/attribute_specification/_1": class std::bad_alloc: bad allocation
  ../testsuite/vhdl/parser_rules/src/test/attribute_specification_test.cpp(46): last checkpoint
  ```

  ToDo: Confirm, that this may occur only in debug mode using MS VC?!

- Add TestCase for assertion_statement, assertion self is tested already. It appends only
  "label: .... ;" to the tests.

- Make Tests to check expectation points for ';'. This days, the error indicator shows
  most of the time to the wrong line/position if is missing. That's correct from parser's
  view (it doesn't rewind the iterator) but confuse the user.

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
  - binding_indication/binding_indication_00{0,1}.input entity name rule 
    (is work.foo -> name)
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

### CMake Build

- Consider use of CMake's [Unity Build Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE)

Read carefully:

- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
  and [Modern CMake Examples](https://github.com/pr0g/cmake-examples)
- also [CMake Discourse](https://discourse.cmake.org/t/one-source-to-create-multiple-objects/2819)
- [C++ dependency management with CMake’s FetchContent](https://medium.com/analytics-vidhya/c-dependency-management-with-cmakes-fetchcontent-4ceca4693a5d)

- **Regards to build options, see [Making CMake work for you](
  http://www.stablecoder.ca/2018/10/30/full-cmake-helper-suite.html)**

### Sources related

- **FixMe**: Before main's init() there is no text style/color functionality even in the
  stacktrace_{gdb,boost} functions.

- position_cache got warnings by compiling with `-Weverything`
  regards to `.line_number()` and `.get_line_start`: IIRC deduction guide, Investigate!

- Simplify formatting output using [fmtlib/fmt](https://github.com/fmtlib/fmt),
  which supports color output; related to C++20 std::format support

- Write git hooks for checking using clang-{tidy,format} et al. Note, that not
  everywhere clang-format may be installed. The git hooks should capture
  - PCH with and without, declarations are hidden in the PCH headers, so if one isn't using
    PCH it results into compile errors.
  - release and debug mode, later one triggers more tests, even using MS compiler.
  - and of course, Linux and Windows, Clang, GNU C++ and MS VC.

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
  to avoid unnecessary rebuild, for an idea look at blender sources. But this clearly
  future work.

### NumericConvert / 2nd pass Parser

  In numeric_convert.cpp a lot of "trickery" is done because of splitting the
  numeric VHDL types into their components by the actual vhdl::parser to save
  parse and check/test time. Even with C++20 there are more possibilities, eg.
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

  Other approaches are shown at [Stackoverflow](
  https://stackoverflow.com/questions/29132809/using-boostspiritqi-to-parse-numbers-with-separators?answertab=active#tab-top)
  but how to cope with error handling than? Hacking X3's internals isn't the way!


## Others

- Get a logo, e.g. ibis as mascot with assets sub directories.

### Testsuite and Boost.Test

- basic_failure_diagnostic_fixture should also save as unified diff, see todo inside header.

- Useful information to store on filesystem are the messages, maybe [Observing test failure messages](
   https://stackoverflow.com/questions/56963902/observing-test-failure-messages/61371602#61371602)

### Documentation

Switch from MarkDown to ReStructuredText. At this state, Doxygen miss some MarkDown
and ReStructuredText features, Sphinx multi projects and doesn't seems to support
Doxygen's Todo tags/list.

Check [LSST DM Developer Guide](https://developer.lsst.io/index.html) for styles
and recommendations.


