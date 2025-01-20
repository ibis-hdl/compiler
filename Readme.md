IBIS HDL project
================

This project aims to become a VHDL compiler.

## Project structure

The project is divided into smaller sub project for maintenance. The idea is to developer parts
independent and use them as library for 3rd party binaries in the future.

Some of these projects exist twice, not yet mature enough to replace the old approach 
(e.g. doc_ng using doxygen and [sphinx](https://www.sphinx-doc.org/)), so both resist 
temporary here.

## Required Tools to Build & Configuration

e.g., see Ubuntu 24.04 [.devcontainer](/.devcontainer)

* C++23 compliant compiler; developed and tested with the big three:
    - [Visual Studio 22 Community Edition](https://visualstudio.microsoft.com/de/vs/community/)
      Command Prompt v17.11.5 (no clang-cl yet due to 
      missing/complete CMake support on project's side at this time)
    - clang++ 19
    - g++ 14

* CMake 3.28
* ninja 1.10

* python 3 for [Conan2](https://conan.io/) and for handling dependencies

and

* lot of memory, highly recommended more than 16GB

## Required 3rd party Libraries

* [Boost](https://www.boost.org/) 1.86
    - spirit X3 (header only)
    - system
    - filesystem
    - locale
    - test (for testsuite)
* [CLI11](https://github.com/CLIUtils/CLI11)
* [{fmt}](https://github.com/fmtlib/fmt)
* [range-v3](https://github.com/ericniebler/range-v3)

see [conanfile.py](/conanfile.py)

## Build

On Windows, open *Visual Studio 2022 Developer Command Prompt* to get the tool chain correct
initialized. On Linux mostly settings are appropriate.

The best to continue is to install [Python's virtual environment](https://docs.python.org/3/library/venv.html) (the option `--system-site-packages` allows usage of the site-packages from the global installation).

> **Note**: You may prefer to name the virtual environment different on Windows (`.win64-venv`) and 
  Linux (`.venv`) if you develop and compile on multi OS setup. Here, I'll use only `.venv` for
  sake of simplicity. \
  Also, always use on Windows the Python Launcher `py` instead `python3` (on Linux).

```shell
> python3 -m venv .venv --system-site-packages
...
```

> **Note**: If you run it from PowerShell, you may have to prepare the 
  [Execution Policies](https://docs.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_execution_policies?view=powershell-7.2) 
  before, see SO [virtualenv in PowerShell?](https://stackoverflow.com/questions/1365081/virtualenv-in-powershell):\
  `> Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process -Force`

and activate Python's virtual environment depend on the OS using:

On Windows:
```powershell
> .win64-venv\Scripts\activate
```

On Linux `bash`:
```shell
> source .venv/bin/activate
```

Check that you are running the right virtual environment by using `pip` (notice capital `V` here),
on PowerShell you may also use `(Get-Command python).path`:

```shell
> pip -V
...
```

Install [Conan](https://conan.io/) as prerequisite into the previous configured virtual 
environment to build the project:

```shell
> pip install conan
...
```

Afterwards you may create a Conan *profile* to build project's dependencies (or even overwrite
an existing one with `--force`). The following will create a **default** Conan *profile*:

```shell
> conan profile detect --force
...
```

Here are several Conan *profiles* used, created by e.g.

```shell
> CXX=clang++ conan profile detect --name clang --force
...
```

which reflects CMake's *presets* used [here](/CMakePresets.json) in the project. 

> **Note**: On Powershell on Windows you may use \
  `> $env:CXX=cl conan profile detect --name msvc --force`


Now, you have to install the dependencies provided by [Conan](https://conan.io/). Since the parameter 
got more complexer over the time a Python script [`conan_install.py`](/conan_install.py) is provided:

```shell
> pip install multipledispatch
> python3 conan_install.py --profile msvc
...
```

Afterwards, you can disable Python's virtual environment by simply

```shell
> deactivate
```

Now you can start to build:

```shell
> cmake --list-presets
...
> cmake --preset <configurePreset-name>
...
> cmake --build --list-presets
...
> cmake --build --preset <buildPreset-name>
...
> ctest --list-presets
...
> ctest --preset <testPreset-name>
...
> cmake --build --preset <testPreset-name> --target help
...
```

## Miscellaneous

Also read
- [Developer](doc/developer.md)
- [ToDo](doc/todo.md)
