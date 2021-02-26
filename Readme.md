EDA project
===========

Required Tools to Build & Configuration
----------------------------------------

* C++17 compliant compiler, tested with
    - clang++ 11, g++10 on Linux (in 2021)
    - g++ 7.3.0 Windows MinGW (in 2018)
    - Visual Studio 2017, Version 15.8 (in 2018)

* cmake 3.18
    - GNU make
    - ninja
    
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

ToDo with respect to Implementation
-----------------------------------

Obviously the intend is to get the parser working and hence the
project.

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

### App Logging

There are several needs to log to the user. The VHDL assert and 
report messages are obvious. Next are messages of warning and errors
from VHDL compiler self. Further internal and debugging messages,
maybe by use of boost.log.


ToDo on design
---------------
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
  with [PCH](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html?highlight=pch) 
  and [reusing them](https://cmake.org/cmake/help/git-stage/command/target_precompile_headers.html) 
  and [Unity Build Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE)
  see also [CMake Discourse](https://discourse.cmake.org/t/one-source-to-create-multiple-objects/2819)

- find a project name, project vhdl is named EDA and the app ibis. Get a logo, e.g. 
  ibis as mascot with assets sub directories.

- By starting using precompiled headers by CMake, some smaller problems rise.
  E.g. *reference to 'util' is ambiguous* error since name lookup got 
  'boost::locale::util' and 'eda::util' for i.e. 'util::user_home_dir'
  at sources/ibis/src/init.cpp - this isn't fatal, but even not tidy.
  
- make clang-tidy and clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the clang-format {off|on}
  especially on class members.
  This also affects cmake/FindClangFormat.cmake

- replace C comments by C++ comments, see e.g. [Github](https://github.com/mbitsnbites/c-comments-to-cpp)
  for a python script. In 2021 it fails with inline comments like signatures
  like foo(int /* unused */). 
  CHECK if there can clang-tidy and clang-format can help

- organize convenience scripts into sub dir - or write a doc how use it on command 
  line for use with copy&paste (best approach IMO).

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

- check git hooks using clang-format
