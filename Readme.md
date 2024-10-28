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
    - Visual Studio 2022 Developer Command Prompt v17.11.5 (not clang-cl due to missing Cmake
      support on project's side at this time)
    - clang++ 18
    - g++ 13

* CMake 3.28
    - ninja 1.10

* python 3 for conan and to generate some project files

* lot of memory, highly recommended more than 16GB

## Required 3rd party Libraries

actually:

* [Boost](https://www.boost.org/) 1.86
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

By using [Conan2 package manager for C and C++](https://github.com/conan-io/conan) with
[CMake wrapper](https://github.com/conan-io/cmake-conan) the libraries are build within
the project. Note, the project aims to be ready for conan v2!

## Build

### Build on Windows

Until 2021 the main developer machine was Fedora/Linux. In 2022 I started with
developing on Windows, using WSL2 and container, also VS Code. But this does not
reflect preference - merely convenience.

Open *Visual Studio 2022 Developer Command Prompt* to get the tool chain correct
initialized.

The best to continue is to install [Python's virtual environment](https://docs.python.org/3/library/venv.html) (the option `--system-site-packages` allows usage of the site-packages from the global installation):

```
> python -m venv .venv --system-site-packages
```

You may use

```
> pip -V
```

to check that you are running the virtual env (notice capital V) for now.

If you run it from PowerShell, you may have to prepare the [Execution Policies](
https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_execution_policies?view=powershell-7.2) before, see
[here](https://stackoverflow.com/questions/1365081/virtualenv-in-powershell):

```
> Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force
> ./.venv/Scripts/activate.ps1
```

Install [conan](https://conan.io/) as prerequisite to build the project:

```
> pip install conan
```

Afterwards you may create a profile for build of project's dependencies (or even overwrite
an existing one with `--force`), e.g. using default MSVC compiler from
[Visual Studio 22 Community Edition](https://visualstudio.microsoft.com/de/vs/community/)

```
> conan profile detect --force
```

or simply use CMake self for setting the ENV variable:

```
> cmake -E env conan profile detect
```

Than you can start to build, i.e.:

```
> conan install . -s compiler.cppstd=17 --output-folder build/conan --build=missing
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

Quite similar to Windows. I also recommend to use [Python's virtual environment](https://docs.python.org/3/library/venv.html) (the option `--system-site-packages` allows usage of the site-packages from the global installation):

```
$ python3 -m venv .venv --system-site-packages
```

and install [conan](https://conan.io/) as prerequisite:

```
$ source ~/.venv/bin/activate
$ pip3 install conan
```

create a profile for Conan, e.g. for use of Clang as compiler for default profile:

```
$ CXX=clang conan profile detect
```

than you can start to build, i.e.:

```
$ conan install . --settings=compiler.cppstd=17 -s "&:build_type=Debug" -s build_type=Release --output-folder build/conan --build=missing
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
