IBIS HDL project
================

This project aims to become a VHDL compiler.

## Project structure

The project is divided into smaller sub project for maintenance. The idea is to developer parts
independent and use them as library for 3rd party binaries in the future.

Some projects exist temporary twice, not yet mature enough to replace the old approach 
(e.g. doc_ng using doxygen and [sphinx](https://www.sphinx-doc.org/)), so both resist here.

## Required Tools to Build & Configuration

e.g., see [.devcontainer](https://github.com/ibis-hdl/compiler/tree/main/.devcontainer)

* C++20 compliant compiler; developed and tested with the big three:
    - Visual Studio 2022 Developer Command Prompt v17.1.6
    - clang++ 14
    - g++ 11

* CMake 3.20
    - ninja 1.10.2

* python 3 for conan and to generate some project files

* lot of memory, highly recommended more than 16GB

## Required 3rd party Libraries

actually:

* [Boost](https://www.boost.org/) 1.78
    - spirit X3 (header only)
    - system
    - filesystem
    - locale
    - test (for testsuite)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [strong_type](https://github.com/rollbear/strong_type)

Until compilers' full C++20/23 support is there:

* [{fmt}](https://github.com/fmtlib/fmt)
* [range-v3](https://github.com/ericniebler/range-v3)

By using [Conan package manager for C and C++](https://github.com/conan-io/conan) with
[CMake wrapper](https://github.com/conan-io/cmake-conan) the libraries are build within
the project. Note, the project aims to be ready for conan v2!

## Build

### Build on Windows

Until 2021 the main developer machine was Fedora/Linux. In 2022 I started with 
developing on Windows, using WSL2 and container, also VS Code. But this does not 
reflect preference - merely convenience.

Open *Visual Studio 2022 Developer Command Prompt* to get the tool chain correct
initialized.

The best to continue is to install [Python's virtual environment](https://docs.python.org/3/library/venv.html):

```
> python -m venv .venv
```

If you run it from PowerShell, you may have to prepare the [Execution Policies](
https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_execution_policies?view=powershell-7.2) before, see
[here](https://stackoverflow.com/questions/1365081/virtualenv-in-powershell):

```
> Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force
> ./.venv/Scripts/activate.ps1
```

Install [conan](https://conan.io/) as prerequisite (as shown above):

```
> pip install conan
```

Afterwards you may create a profile for build of project's dependencies. Conan v2 will require it 
(these days you got only a waning about), e.g. using MSVC with Powershell

```
> $env:CONAN_V2_MODE=1
> conan profile new msvc --detect
```

or simply use CMake self for setting the ENV variable:

```
> cmake -E env CONAN_V2_MODE=1 conan profile new msvc --detect
```

Than you can start to build, i.e.:

```
> conan install . --install-folder conan/Release --remote=conancenter --profile:build=msvc `
  --build=missing --settings build_type=Release
...
> cmake --list-presets=all
...
> cmake --preset windows-msvc-release
...
> cmake --build --preset windows-msvc-release --target clean
...
> cmake --build --preset windows-msvc-release
...
> cmake --build --preset windows-msvc-release --target doc
...
> ctest --preset windows-msvc-release
...
```

### Build on Linux

Quite similar to Windows. I also recommend to use [Python's virtual environment](https://docs.python.org/3/library/venv.html):

```
$ python -m venv .venv
```

and install [conan](https://conan.io/) as prerequisite:

```
$ source ~/.venv/bin/activate
$ pip install conan
```

create a profile for Conan, e.g. for use of Clang[^conan-clang-profile] as compiler of
depend libraries:

[^conan-clang-profile]: see [Detect libstdc++ ABI mode when using Clang on Linux #11886](
  https://github.com/conan-io/conan/pull/11886)


```
$ export CONAN_V2_MODE=1
$ CXX=clang conan profile new clang --detect
```

than you can start to build, i.e.:

```
$ conan install . --install-folder conan/Release --remote=conancenter --profile:build=clang \
  --build=missing --settings build_type=Release
...
$ cmake --list-presets=all
...
$ cmake --preset linux-clang-release
...
$ cmake --build --preset linux-clang-release --target clean
...
$ cmake --build --preset linux-clang-release
...
$ cmake --build --preset linux-clang-release --target doc
...
$ ctest --preset linux-clang-release
...
```

The same procedure for GCC.

## Miscellaneous

Also read
- [Developer](doc/developer.md)
- [ToDo](doc/todo.md)

