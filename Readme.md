EDA project
===========

Required Tools to Build & Configuration
----------------------------------------

* C++17 compliant compiler, tested with
    - clang++ 11 (in 2021), g++10 untested
    - g++ 7.3.0 Windows MinGW (in 2018)
    - Visual Studio 2017, Version 15.8 (in 2018)

* cmake 3.18
    - ninja (GNU make not well supported by the maintainer)
    
* python 3 to generate some files

* A lot of memory, highly recommended are 16GB


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
* GLS (unused yet)


ToDo with respect to Implementation
-----------------------------------

Obviously the intend is to get the parser working and hence the
project.


### Code Fixes

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

  Really time to change to boost.property library.

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

- maybe move the testsuits below there sources, see e.g. llvm source tree

### CMake

- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
  and [Modern CMake Examples](https://github.com/pr0g/cmake-examples)
- [PCH](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html?highlight=pch) 
  and [reusing them](https://cmake.org/cmake/help/git-stage/command/target_precompile_headers.html) 
- [Unity Build Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE)
  see also [CMake Discourse](https://discourse.cmake.org/t/one-source-to-create-multiple-objects/2819)
- [C++ dependency management with CMake’s FetchContent](https://medium.com/analytics-vidhya/c-dependency-management-with-cmakes-fetchcontent-4ceca4693a5d)

- By starting using precompiled headers by CMake, some smaller problems rise.
  E.g. *reference to 'util' is ambiguous* error since name lookup got 
  'boost::locale::util' and 'eda::util' for i.e. 'util::user_home_dir'
  at sources/ibis/src/init.cpp - this isn't fatal, but even not tidy.
  
- l10n seems to have a problem with PCH support, warning/error rises:
  "xgettext: error while opening "../sources/common//..cmake_pch.hxx.cxx"
  for reading: No such file or directory

- boost.test has also problems with PCH, the main() is missing on linker time even
  it compiles find without PCH support.

### Sources

- **FixMe**: As shown in the past, if main's init() function crash and the color
  code isn't configured, we don't have these functionality even in the
  stacktrace_{gdb,boost} functions. Maybe a color 'lite support' may solve it, see
  [boost.UTF setcolor()](https://github.com/boostorg/test/blob/9d863d07e864ef663e3e8573b55905099b938d3e/include/boost/test/utils/setcolor.hpp)
  or even use eda::color code with defaults set before - see 
  init::user_config_message_color(). Maybe initialize the streams really early
  inside init().

- Replace C comments by C++ comments, see e.g. [Github](https://github.com/mbitsnbites/c-comments-to-cpp)
  for a python script. In 2021 it fails with inline comments like signatures
  like foo(int /* unused */). 
  CHECK if there can clang-tidy and clang-format can help

- Get clang-tidy and clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the '// 'clang-format {off|on}'
  pragmas especially on class members.
  A good starting point is 
  [Static checks with CMake/CDash (iwyu, clang-tidy, lwyu, cpplint and cppcheck)](
  https://blog.kitware.com/static-checks-with-cmake-cdash-iwyu-clang-tidy-lwyu-cpplint-and-cppcheck/)
  
  - $ cmake "-DCMAKE_CXX_CLANG_TIDY=clang-tidy" ../path/to/source
    or simply enable the option DEVELOPER_RUN_CLANG_TIDY or run build
    tool, e.g. ninja. The projects compiles with clang-tidy in front of-
  - testsuite is heavy to improve due to heavy use of macros by boost.test
  - not checked by clang-{tidy,format}:

    1. RapidJSON parts of init.cpp isn't checked since it may be replaced
      by boost.json
    2. ibis/src/stacktrace_{boost,gdb}.cpp since they need more effort
      to check and rewrite/improve

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

  - make a contest for ast_walker, like

  struct ast_walker::context {
      std::string_view current_node_name();
      int64_t recursive_depth();
  };

  - use for recursive depth counting a class with ctor/dtor increment/decrement 
    capabilities - recursive_depth_{counter,guard}

  -  ast_stats.cpp:
    - ast_stats sort order - use enum sort::{ascending, descending}
    - worker collector{ count_map, untagged_nodes } fix to
      worker stats_worker{ count_map, untagged_nodes };


### Others

- find a project name, project vhdl is named EDA and the app ibis. Get a logo, e.g. 
  ibis as mascot with assets sub directories.

- organize convenience scripts into sub dir - or write a doc how use it on command 
  line for use with copy&paste (best approach IMO).


C++ Code style
--------------

### C++ preprocessing
See [Undefining the C++ Pre-processor](https://cor3ntin.github.io/posts/undef_preprocessor/)

### CLang Tidy

See project's .clang-tidy' and 
[protozero/.clang-tidy](https://github.com/mapbox/protozero/blob/master/.clang-tidy)

Reworking for Options from 2018, here for reference:

```
---
Checks: "-*,\
cert-*,\
-cert-err58-cpp,\
clang-analyzer-*,\
-clang-analyzer-optin.cplusplus.VirtualCall,\
cppcoreguidelines-*,\
-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
-cppcoreguidelines-pro-type-const-cast,\
-cppcoreguidelines-pro-type-member-init,\
-cppcoreguidelines-pro-type-vararg,\
-cppcoreguidelines-avoid-magic-numbers,\
misc-*,\
modernize-*,\
-modernize-use-trailing-return-type,\
-modernize-concat-nested-namespaces,\
readability-*,\
-readability-magic-numbers,\
-readability-redundant-access-specifiers,\
performance-*,\
"
HeaderFilterRegex: '*\.(hpp|h)$'
...
```

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
   [std::source_location](https://en.cppreference.com/w/cpp/utility/source_location) which simplifies assert macros.*

- [bugprone-*](https://clang.llvm.org/extra/clang-tidy/checks/list.html):  
  *Check & try me*

#### permanently disabled

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):  
  *This transformation is purely stylistic. We are not quite that modern.*

- [readability-magic-numbers](https://clang.llvm.org/extra/clang-tidy/checks/readability-magic-numbers.html), cppcoreguidelines-avoid-magic-numbers:  
  *This goes too far to force this everywhere. Also, it's not applicable mostly here.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):  
  *It's correct, but serves here for segmentation in their tasks or functions.*
  
