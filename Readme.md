IBIS HDL project
================

Required Tools to Build & Configuration
----------------------------------------

* C++17 compliant compiler, tested with
    - clang++ 11 (in 2021), g++10 untested
    - g++ 7.3.0 Windows MinGW (in 2018)
    - Visual Studio 2017, Version 15.8 (in 2018)

* cmake 3.18
    - ninja (recommended)
    - GNU make (not well supported by maintainer)

* python 3 to generate some files

* much memory, highly recommended more than 16GB


Required 3rd party Libraries
----------------------------

* Boost 1.73
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)

The following libraries are downloaded automatically into project's external
directory from git repositories:

* CLI11
* GLS (currently unused)

Build
-----

### For end user

There is nothing of interest at this time, really.

### For developer

There are some environment variables for the clang tools:

- CLANG_TIDY_ROOT_DIR
- CLANG_FORMAT_ROOT_DIR

One may run into Clang specific linker error:

```
/usr/bin/ld: cannot find /usr/lib64/libasan.so.6.0.0
collect2: error: ld returned 1 exit status
```
than simply install libasan, e.g. on Fedora:
```
$ sudo dnf install libasan libasan-static
```

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

#### ToDo

- MaybeOfInterest:
  - https://github.com/ddemidov/amgcl/blob/master/CMakeLists.txt
  - https://github.com/AmokHuginnsson/replxx/blob/master/CMakeLists.txt


-  Ninja parallel build:
  - https://github.com/microsoft/DirectXShaderCompiler/blob/master/CMakeLists.txt
  - https://github.com/Bforartists/Bforartists/blob/master/CMakeLists.txt

- for cmake tidy && format, code coverage etc. example code look at
  https://github.com/ORNL-CEES/mfmg/tree/master/cmake

- Unit Testing
  - https://github.com/onqtam/awesome-cmake/blob/master/README.md#toolchains
  - https://github.com/adishavit/cmake_snippets


#### Running tests

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


ToDo with respect to Implementation
-----------------------------------

Obviously the intend is to get the parser working and hence the
project.


### Code Fixes


#### Fix Clang AddressSanitizer issue

```
stack-buffer-overflow .../color/detail/ansi_color.hpp:33 in
color::detail::esc_printer<ibis::color::attribute, 4ul>::esc_printer<0ul, 1ul, 2ul, 3ul>(
  std::initializer_list<ibis::color::attribute>,
  std::integer_sequence<unsigned long, 0ul, 1ul, 2ul, 3ul>
)
```

From IRC:

```
you seem to be passing in an initializer_list which has one element but you're accessing il.begin()[0] through il.begin()[3]?
<Alipha> olx69: do you want to initialize all 4 elements to attribute::Attributes_Off?
```

Maybe related is compiler's warning seen on older code:

```
source/common/include/ibis/color/detail/ansii_color.hpp:33:43: Warnung: Arrayindex 1 ist außerhalb der Arraygrenzen von »const ibis::color::attribute [1]« [-Warray-bounds]
   33 |         : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N])... } }
      |                                           ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
source/common/include/ibis/color/detail/ansii_color.hpp:130:49: Anmerkung: beim Referenzieren von »<anonymous>«
  130 | color::printer const bold{ attribute::Text_Bold };
      |                                                 ^
source/common/include/ibis/color/detail/ansii_color.hpp:33:43: Warnung: Arrayindex 2 ist außerhalb der Arraygrenzen von »const ibis::color::attribute [1]« [-Warray-bounds]
   33 |         : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N])... } }
      |                                           ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
source/common/include/ibis/color/detail/ansii_color.hpp:130:49: Anmerkung: beim Referenzieren von »<anonymous>«
  130 | color::printer const bold{ attribute::Text_Bold };
      |                                                 ^
source/common/include/ibis/color/detail/ansii_color.hpp:33:43: Warnung: Arrayindex 3 ist außerhalb der Arraygrenzen von »const ibis::color::attribute [1]« [-Warray-bounds]
   33 |         : std::array<value_type, SIZE>{ { static_cast<value_type>(il.begin()[N])... } }
      |                                           ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
source/common/include/ibis/color/detail/ansii_color.hpp:130:49: Anmerkung: beim Referenzieren von »<anonymous>«
  130 | color::printer const bold{ attribute::Text_Bold };
      |                                                 ^
```

#### Boost.Spirit X3 Notes

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

- Check [**Splitting Boost.Spirit.X3 parsers into several TUs**](
  https://stackoverflow.com/questions/59709229/splitting-boost-spirit-x3-parsers-into-several-tus)

- Check [Trying to convert a VHDL BNF to a labeled BNF for BNFC](
  https://stackoverflow.com/questions/44166199/trying-to-convert-a-vhdl-bnf-to-a-labeled-bnf-for-bnfc)


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

It is even reproducible with the code of 2018 (git tag R2018) and
Boost's v1.73 spirit X3 by setting CMake's ExternalProject_Add()
GIT_TAG from 1.68.0 to 1.73 (see options_developer.cmake). So these
errors are imminent in these code base before. Anyway, parser is
still the main work ground.

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
maybe by use of boost.log.

Generally, a lot of information go trough std::cerr without prefix
or even using colorizing. E.g. on stacktrace_{gdb.boost} it's not
clear what comes from what.


ToDo on design
---------------

### Project structure

- testsuite/util/basic_failure_diagnostic_fixture and testsuite/vhdl/util/failure_diagnostic_fixture
  still BAD NAMING ...

- merge back testsuite librules into parser_rules. The intention was
  to split out compile/memory intensive compile jobs. This is
  confusing from maintenance aspect. This may be complicated, so the impression
  after some test. The linker run out of memory with 20GB... Maybe a compiler
  template firewall must be introduced, see
  [Internal compiler error, while using boost spirit x3](
   https://stackoverflow.com/questions/40195894/internal-compiler-error-while-using-boost-spirit-x3).
  Maybe the reason was, that all optimizations where turned off? to save
  time.


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

- **FetchContent** would work as shown below, if the depend content wouldn't
  use the same targets as my in their CMakeLists, e.g. custom_target doc
  at RapidJSON.

```
include(FetchContent)

FetchContent_Declare(RapidJSON
  GIT_REPOSITORY    https://github.com/Tencent/rapidjson.git
  GIT_TAG           master
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
)

FetchContent_MakeAvailable(RapidJSON)
set(RapidJSON_INCLUDE_DIR "${RapidJSON_SOURCE_DIR}/include" CACHE STRING "")
```


### Sources

- **FixMe**: Before main's init() there is no text style/color functionality even in the
  stacktrace_{gdb,boost} functions.

- Simplify formatting output using [fmtlib/fmt](https://github.com/fmtlib/fmt),
  which supports color output; related to C++20 std::format support

- Get clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the '// 'clang-format {off|on}'
  pragmas especially on class members.

- Write git hooks for checking using clang-{tidy,format} et al. Note, that not
  everywhere clang-format may be installed.

- join back testsuite's librules into parser_rules. The reason was in 2018 the
  compilation effort: compiling with make -j X and spirit.x3 rules with
  single core. Starting with CMake 3.16 there is the Unity Build Mode.

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

- Write a formatter for all error report classes/functions, e.g. parser::error_handler.
  An idea may be [Controlling output of Boost.Test source location format](
  https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format).


### Others

- Get a logo, e.g. ibis as mascot with assets sub directories.


### Boost.Test

An interesting feature is described at
[Controlling output of Boost.Test source location format](
  https://stackoverflow.com/questions/64618840/controlling-output-of-boost-test-source-location-format)


C++ Code style
--------------

Check [LSST DM Developer Guide](https://developer.lsst.io/index.html) for styles
and recommendations.


### CLang Tidy

A good starting point is [Static checks with CMake/CDash (iwyu, clang-tidy, lwyu, cpplint and cppcheck)](
https://blog.kitware.com/static-checks-with-cmake-cdash-iwyu-clang-tidy-lwyu-cpplint-and-cppcheck/)

  - not checked in deep by clang-tidy:

    - frontend/src/stacktrace_{boost,gdb}.cpp since they need more effort
      to check and rewrite/improve


#### FixMe

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
  checks also examines conditional operators, so we can't it disable completely.

- [readability-identifier-naming](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
  *Here a lot of effort is required to consolidate and unify all the naming*, e.g. see
  [.clang-tidy](https://github.com/xournalpp/xournalpp/blob/master/.clang-tidy) or
  [.clang-tidy](https://github.com/ROCmSoftwarePlatform/AMDMIGraphX/blob/develop/.clang-tidy) as example.

#### permanently disabled

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):
  *This transformation is purely stylistic. We are not quite that modern.*

- [readability-magic-numbers](https://clang.llvm.org/extra/clang-tidy/checks/readability-magic-numbers.html), cppcoreguidelines-avoid-magic-numbers:
  *This goes too far to force this everywhere.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):
  *This is correct, but is used here for classification purposes.*

- [cppcoreguidelines-pro-type-vararg](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-type-vararg.html):
  *By using Boost UTF this rule is triggered on each BOOST_TEST macros. No c-style vararg functions are written in this project.*


## ToDo Documentation

Switch from MarkDown to ReStructuredText. At this state, Doxygen miss some MarkDown
and ReStructuredText features, Sphinx multi projects and doesn't seems to support
Doxygen's Todo tags/list.

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

