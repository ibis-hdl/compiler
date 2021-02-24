EDA project
===========

Required Tools to Build & Configuration
----------------------------------------

* C++17 compliant compiler, tested with
    - clang++ 5.0, g++7.3.1 on Linux
    - g++ 7.3.0 Windows MinGW
    - Visual Studio 2017, Version 15.8

* cmake 3.18
    - GNU make
    - ninja
    
* python 3.6 to generate some files


Required 3rd party Libraries
----------------------------

* Boost 1.73
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)
    
* CLI11 (bundled)

The following libraries are downloaded autmatically into project's external
directory:

* RapidJSON


ToDo on design
---------------
- By starting using precompiled headers by cmake, some smaller problems rise.
  E.g. *reference to 'util' is ambiguous* error since name lookup got 
  'boost::locale::util' and 'eda::util' for i.e. 'util::user_home_dir'. 
  This isn't fatal, but even not tidy.
  
- Upgrade to CLI11 1.9.1, see
  https://github.com/CLIUtils/CLI11/issues/562
    
