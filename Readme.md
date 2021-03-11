EDA project
===========

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

* much memory, highly recommended are 16GB


Required 3rd party Libraries
----------------------------

* Boost 1.73
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)
    
The following libraries are downloaded automatically into project's external
directory from git repositories:

* RapidJSON
* CLI11
* GLS (currently unused)

Build
-----

### For end user

There is nothing to build currently, really.

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


#### ToDo

- MaybeOfInterest:
  - https://github.com/ddemidov/amgcl/blob/master/CMakeLists.txt
  - https://github.com/AmokHuginnsson/replxx/blob/master/CMakeLists.txt


-  Ninja parallel build:
  - https://github.com/microsoft/DirectXShaderCompiler/blob/master/CMakeLists.txt
  - https://github.com/Bforartists/Bforartists/blob/master/CMakeLists.txt

- [cheshirekow/cmake_format](https://github.com/cheshirekow/cmake_format)


- [git-cmake-format](https://github.com/BlueBrain/git-cmake-format)
  This project aims to provide a quick and easy way to integrate clang-format into your CMake project hosted in a git repository

- cmake tidy && format example code
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


ToDo with respect to Implementation
-----------------------------------

Obviously the intend is to get the parser working and hence the
project.


### Code Fixes


#### Fix Clang AddressSanitizer issue

```
stack-buffer-overflow .../color/detail/ansii_color.hpp:33 in 
color::detail::esc_printer<eda::color::attribute, 4ul>::esc_printer<0ul, 1ul, 2ul, 3ul>(
  std::initializer_list<eda::color::attribute>, 
  std::integer_sequence<unsigned long, 0ul, 1ul, 2ul, 3ul>
)
```

From IRC:

```
you seem to be passing in an initializer_list which has one element but you're accessing il.begin()[0] through il.begin()[3]?
<Alipha> olx69: do you want to initialize all 4 elements to attribute::Attributes_Off?
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

Check [**Splitting Boost.Spirit.X3 parsers into several TUs**](
  https://stackoverflow.com/questions/59709229/splitting-boost-spirit-x3-parsers-into-several-tus)


#### Settings Crash

An old problem from beginning rises, see [wandbox](https://wandbox.org/permlink/SklFbT05oHEGFhqW)
which isn't obviously solved.

```
#17 ibis::init::l10n (this=...) at .../sources/ibis/src/init.cpp:513
```

where:

```
long const verbose = [&] { return setting["verbose"].get<long>(); }();
```

rises an exception

```
terminate called after throwing an instance of 'std::bad_variant_access'
  what():  std::get: wrong index for variant
```

thrown from

```
#16 eda::settings::option_value_proxy::get<long> (this=....>) at .../sources/common/include/eda/settings.hpp:107
```

The source is the boost::variant visitor:

```
template <typename T> T const& get() const
{
    // bad_variant_access thrown on invalid accesses to the value
    return std::get<T>(option_value);
}
```

  Really time to change to boost.property library. Unfortunately, it can not be
  reproduced later on.

### Fix Parser Testsuite

IIRC the tests passed in 2018. Only problems mentioned in vhdl parser_rules
*test_case_FixMe.txt* where known. In 2021 following test
*test_vhdl_parser_rule* tests failed:

  - test_case_name = aggregate/aggregate_001; 
  - test_case_name = aggregate/aggregate_002; 
  - test_case_name = aggregate/aggregate_003; 
  - test_case_name = aggregate/aggregate_006; 
  - test_case_name = attribute_specification/attribute_specification_001; 
  - test_case_name = use_clause/use_clause_000; 

In 2021, the code of 2018 (git tag R2018) compiles and runs without errors
regards to grammar rules.
Other test are fine. Anyway, this is still the main work ground.

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

- merge back testsuite librules into parser_rules. The intention was
  to split out compile/memory intensive compile jobs. This is 
  confusing from maintenance aspect. The best would be to use ninja
  specific switches in CMake. Maybe better to complete switch to ninja.

- maybe move the testsuites below there sources, see e.g. llvm source tree

### CMake

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

- By starting using precompiled headers by CMake, some smaller problems rise.
  E.g. *reference to 'util' is ambiguous* error since name lookup got 
  'boost::locale::util' and 'eda::util' for i.e. 'util::user_home_dir'
  at sources/ibis/src/init.cpp - this isn't fatal, but even not tidy.
  
- l10n seems to have a problem with PCH support, warning/error rises:
  "xgettext: error while opening "../sources/common//..cmake_pch.hxx.cxx"
  for reading: No such file or directory

- boost.test has also problems with PCH, the main() is missing on linker time even
  it compiles find without PCH support.

- Miss ome CMake variables? Try [Displaying CMake Variables](
   https://stackoverflow.com/questions/31343813/displaying-cmake-variables)

- use [cmake-format](https://github.com/cheshirekow/cmake_format)
  ```pip install cmakelang```. Anyway, the results doesn't impress me...

### Sources

- **FixMe**: As shown in the past, if main's init() function crash and the color
  code isn't configured, we don't have these functionality even in the
  stacktrace_{gdb,boost} functions. Maybe a color 'lite support' may solve it, see
  [boost.UTF setcolor()](https://github.com/boostorg/test/blob/9d863d07e864ef663e3e8573b55905099b938d3e/include/boost/test/utils/setcolor.hpp)
  or even use eda::color code with defaults set before - see 
  init::user_config_message_color(). Maybe initialize the streams really early
  inside init().

- Make the path of test inputs hard coded using CMake's configure_file() to run
  int easily without ctest and command line arguments. They are not intended
  to be distributed, so it doesn't matter. But, don't remove the command line
  options to explicit override these paths other specific tests.
  After first inspection, more effort is required for parse_rules and syntax
  testsuite since the concept of parsing command line arguments, using builtin
  compile path and naming of tests isn't appropriate to this.

- Replace C comments by C++ comments, see e.g. [Github](https://github.com/mbitsnbites/c-comments-to-cpp)
  for a python script. In 2021 it fails with inline comments like signatures
  like foo(int /* unused */). 
  CHECK if there can clang-tidy and clang-format can help

- Get clang-tidy and clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the '// 'clang-format {off|on}'
  pragmas especially on class members.
  
- Write git hooks for checking using clang-{tidy,format} et al.

- Replace:
  - boost.filesystem with std::filesystem, check it before for compliance of 
    used functions.
  - RapidJSON with boost.json - starting with boost 1.75. The results of
    [Benchmarks](https://vinniefalco.github.io/doc/json/json/benchmarks.html) 
    look promising
  - util::visit_in_place using boost.hana with util::overloaded
  - swap from make to ninja build to use CMake's Unity Build Mode
  - unify and simplify the build helper scripts
  - join back testsuite's librules into parser_rules. The reason was in 2018 the 
    compilation effort: compiling with make -j X and spirit.x3 rules with 
    single core. Starting with CMake 3.16 there is the Unity Build Mode.


- AST printer: move ast_printer into ast_walker, printer breaks down into simple class
  like ast_stats.

  - use for recursive depth counting a class with ctor/dtor increment/decrement 
    capabilities - recursive_depth_{counter,guard} - as context i.e.

  -  ast_stats.cpp:
    - ast_stats sort order - use enum sort::{ascending, descending}
    - worker collector{ count_map, untagged_nodes } fix to
      worker stats_worker{ count_map, untagged_nodes };


### Others

- find a project name, project vhdl is named EDA and the app ibis. Get a logo, e.g. 
  ibis as mascot with assets sub directories.

- organize convenience scripts into sub dir - or write a doc how use it on command 
  line for use with copy&paste (best approach IMO).

### MS VS

Support Clang on Windows, see [Clang's MSVC compatibility](https://clang.llvm.org/docs/MSVCCompatibility.html)


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
  
  - $ cmake "-DCMAKE_CXX_CLANG_TIDY=clang-tidy" ../path/to/source
    or simply enable the option DEVELOPER_RUN_CLANG_TIDY or run build
    tool, e.g. ninja. The projects compiles with clang-tidy in front of-
  - testsuite is heavy to improve due to heavy use of macros by boost.test
  - not checked by clang-{tidy,format}:

    - RapidJSON parts of init.cpp isn't checked since it may be replaced
      by boost.json
    - ibis/src/stacktrace_{boost,gdb}.cpp since they need more effort
      to check and rewrite/improve


#### FixMe

- [misc-no-recursion](https://clang.llvm.org/extra/clang-tidy/checks/misc-no-recursion.html):  
  *Until the ast_printer recursive call chain has been solved.*

- modernize-concat-nested-namespaces:  
  *ToDo: can be done be clang-format?*

- [cert-err58-cpp](https://clang.llvm.org/extra/clang-tidy/checks/cert-err58-cpp.html):  
  *It's correct, but depend on others libraries.*

- [cppcoreguidelines-pro-bounds-array-to-pointer-decay](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay.html):  
  *Ignored at this time. With C++20 with get [std::span](https://en.cppreference.com/w/cpp/container/span) 
   aka gsl::span aka gsl:: gsl::array_view. Also starting with C++20 we has also 
   [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location) which allows to write assert macros with C++20.*

- [bugprone-*](https://clang.llvm.org/extra/clang-tidy/checks/list.html):  
  *Check & try me*

#### permanently disabled

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):  
  *This transformation is purely stylistic. We are not quite that modern.*

- [readability-magic-numbers](https://clang.llvm.org/extra/clang-tidy/checks/readability-magic-numbers.html), cppcoreguidelines-avoid-magic-numbers:  
  *This goes too far to force this everywhere.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):  
  *This is correct, but is used here for classification purposes.*
  
## ToDo Documentation

Switch from MarkDown to ReStructuredText.

- [Clear, Functional C++ Documentation with Sphinx + Breathe + Doxygen + CMake](
   https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/)

- [C++ documentation with Doxygen/CMake/Sphinx/Breathe for those of us who are totally lost Part 1](
   https://medium.com/practical-coding/c-documentation-with-doxygen-cmake-sphinx-breathe-for-those-of-use-who-are-totally-lost-7d555386fe13),
  [Part 2](https://medium.com/practical-coding/c-documentation-with-doxygen-cmake-sphinx-breathe-for-those-of-use-who-are-totally-lost-part-2-21f4fb1abd9f)
  and [Part 3](https://medium.com/practical-coding/c-documentation-with-doxygen-cmake-sphinx-breathe-for-those-of-use-who-are-totally-lost-part-3-d20549d3b01f)

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

- Sphinx example projects:
  - https://github.com/ainfosec/ci_helloworld
  - https://github.com/normalvector/ue4_doxygen_source_filter
  - https://github.com/svenevs/exhale

A more sophisticated INPUT filter for doxygen:
  - https://stackoverflow.com/questions/44166199/trying-to-convert-a-vhdl-bnf-to-a-labeled-bnf-for-bnfc

