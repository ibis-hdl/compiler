EDA project
===========

Required Tools to Build & Configuration
----------------------------------------

* C++17 compliant compiler, tested with
    - clang++ 5.0, g++7.3.1 on Linux
    - g++ 7.3.0 Windows MinGW
    - Visual Studio 2017, Version 15.8

* cmake 3.12
    - GNU make
    - ninja 1.8.2 (tested)
    
* python 3.6 to generate some files


Required 3rd party Libraries
----------------------------

* Boost 1.67
    - filesystem
    - locale
    - spirit X3
    - test (for testsuite)
    
* CLI11 (bundled)

The following libraries are downloaded autmatically into project's external
directory:

* RapidJSON
