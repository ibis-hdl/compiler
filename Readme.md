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


Required 3rd party Libraries
----------------------------

* Boost 1.73
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)
    
The following libraries are downloaded autmatically into project's external
directory from git repositories:

* RapidJSON
* CLI11


ToDo by design
---------------
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)
  with [PCH](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html?highlight=pch) 
  and [reusing them](https://cmake.org/cmake/help/git-stage/command/target_precompile_headers.html) 
  and [Unitiy Bild Mode](https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html#prop_tgt:UNITY_BUILD_MODE)
  see also [CMake Discouse](https://discourse.cmake.org/t/one-source-to-create-multiple-objects/2819)

- find a project name, vhdl is EDA and the app ibis. Get a logo, e.g. ibis
  as mascot with assets subdir.

- By starting using precompiled headers by cmake, some smaller problems rise.
  E.g. *reference to 'util' is ambiguous* error since name lookup got 
  'boost::locale::util' and 'eda::util' for i.e. 'util::user_home_dir'
  at sources/ibis/src/init.cpp - this isn't fatal, but even not tidy.
  
- make clang-tidy and clang-format working again. By The Way, check clang-format
  style for enhancements, so that we get rid off the clang-format {off|on}
  especially on class members.
  This also affects cmake/FindClangFormat.cmake

- replace C comments by C++ comments, see e.g. [Github](https://github.com/mbitsnbites/c-comments-to-cpp)
  for a python script. In 2021 it fails witj inline comments like signatures
  like foo(int /* unsued */). 
  CHECK if there can clang-tidy and clang-format can help

- organize convinience scripts into sub dir

- Replace:
  - boost.filesystem with std::filesystem, check it before for compliance of 
    used functions.
  - util::visit_in_place using boost.hana with util::overloaded
  - swap from make to ninja build to use CMake's Unitiy Bild Mode
  - unify and simplify the build helper scripts
  - join back testsuit's librules into parser_rules. The reason was in 2018 the 
    compilation effort: compiling with make -j X and spirit.x3 rules with 
    single core. Starting with CMake 3.16 there is the Unitiy Bild Mode.

- check git hooks using clang-format