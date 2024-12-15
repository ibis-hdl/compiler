IBIS HDL project
================

This project aims to become a VHDL compiler.

## Build the `update-2024` branch

## Customize CMake build

CMake supports two files, `CMakePresets.json` and `CMakeUserPresets.json`, that allow users to 
specify common configure, build, and test options and share them with others. For more
information see [cmake-presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html).

To use, e.g. [Ccache (a fast C/C++ compiler cache)](https://ccache.dev/) for CMake's configure phase, write your own `CMakeUserPresets.json` with

```json
{
    "version": 8,
    "include": [
        "cmake/presets/common.json"
    ], 
    "configurePresets": [
        {
            "name": "ccache-gcc",
            "displayName": "GnuC (ccache)",
            "description": "GnuC compiler using compiler cache",
            "inherits": [
                "gcc",
                "ccache"
            ]
        }
    ]
}
```

The build and test presets remain. The JSON `common.json` already contains a predefined "ccache" section:

```
        {
            "name": "ccache",
            "description": "ccache - compiler cache",
            "hidden": true,
            "cacheVariables": {
                "CMAKE_CXX_COMPILER_LAUNCHER": "ccache",
                "CCACHE_BASEDIR": "${sourceDir}",
                "CCACHE_SLOPPINESS": "pch_defines,time_macros",
                "CCACHE_DIR": "~/.cache/ccache" 
            }
        },
```

### on Windows

Ensure you have VS 2022 (Community).

```powershell
> virtualenv .win64-venv
...
> .\.win64-venv\Scripts\activate
> pip install -r requirements.txt
...
> py .\conan_install.py --profile msvc
...
> cmake --preset msvc
...
> cmake --build --preset msvc-release
...
> ctest.exe --preset msvc-release-test
...
```


## Project structure

The project is divided into smaller sub project for maintenance. The idea is to developer parts
independent and use them as library for 3rd party binaries in the future.

Some projects exist temporary twice, not yet mature enough to replace the old approach
(e.g. doc_ng using doxygen and [sphinx](https://www.sphinx-doc.org/)), so both resist here.

## Required Tools to Build & Configuration

e.g., see [.devcontainer](https://github.com/ibis-hdl/compiler/tree/main/.devcontainer)

* C++20 compliant compiler; developed and tested with the big three:
    - Visual Studio 2022 Developer Command Prompt v17.11.5 (not clang-cl due to missing CMake
      support on project's side at this time)
    - clang++ 18
    - g++ 13

* CMake 3.28
    - ninja 1.10

* python 3 for [Conan2](https://conan.io/) and for handling dependencies

and

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

## Build

### Build on Windows

Until 2021 the main developer machine was Fedora/Linux. In 2022 I started with
developing on Windows, using WSL2 and container, also VS Code. But this does not
reflect preference - merely convenience.

Open *Visual Studio 2022 Developer Command Prompt* to get the tool chain correct
initialized.

The best to continue is to install [Python's virtual environment](https://docs.python.org/3/library/venv.html) (the option `--system-site-packages` allows usage of the site-packages from the global installation):

```
> py -m venv .venv --system-site-packages
```

If you run it from PowerShell, you may have to prepare the [Execution Policies](
https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_execution_policies?view=powershell-7.2) before, see
[here](https://stackoverflow.com/questions/1365081/virtualenv-in-powershell):

```
> Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force
> ./.venv/Scripts/activate
```

In PowerShell you may use `$ Get-Command python`, or even

```
> pip -V
```

to check that you are running the virtual env (notice capital V here) for now.

Install [Conan](https://conan.io/) as prerequisite to build the project:

```
> pip install conan
```

Afterwards you may create a profile for build of project's dependencies (or even overwrite
an existing one with `--force`), e.g. using default MSVC compiler from
[Visual Studio 22 Community Edition](https://visualstudio.microsoft.com/de/vs/community/)

```
> conan profile detect --force
```

or simply use [CMake](https://cmake.org) self for setting the environment variable:

```
> cmake -E env conan profile detect
```

Now, you have to install the dependencies provided by [Conan](https://conan.io/):

```
> conan install . -s compiler.cppstd=17 --output-folder build/conan --build=missing
...
```

Afterwards, you can disable Python's virtual environment by simply

```
> deactivate
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

and install [Conan](https://conan.io/) as prerequisite:

```
$ source ~/.venv/bin/activate
$ pip3 install conan
```

create a profile for [Conan](https://conan.io/), e.g. for use of Clang as compiler for default profile:

```
$ CXX=clang conan profile detect
```

Now, you have to install the dependencies provided by [Conan](https://conan.io/):

```
> conan install . -s compiler.cppstd=17 --output-folder build/conan --build=missing
...
```

Than you can start to build, i.e.:

```
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
