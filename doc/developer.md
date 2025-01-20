Developer
=========

Generally honor:

- [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html)

**More serious**: The source code has partially doxygen documentation which is
partially expressive, but outdated. A documentation marathon is required if the
source base is **stable**.

## Build: Requisites

For Ubuntu please have a look at the files in [`.devcontainer`](../.devcontainer) and the scripts.

For Fedora:

```shell
sudo dnf install gcc clang clang-tools-extra cmake ninja-build
```

## Build: Conan Profile

It is important to set up the right Conan profile, e.g. setup the right compiler and path. E.g.
for Clang profile `clang`, `[buildenv]`and `[conf]` are added manually:

```shell
$ cat .conan2/profiles/clang 
[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=19
os=Linux

[buildenv]
CC=clang
CXX=clang++

[conf]
tools.build:compiler_executables={ "c": "/usr/bin/clang", "cpp": "/usr/bin/clang++" }
```

Further, if during `conan install` one gets
 `c++: error: unrecognized command-line option ‘-stdlib=libstdc++’`
 then the compiler aren't correctly setup - it's not a valid flag for GCC.

## Build: Customize CMake build

CMake supports two files, `CMakePresets.json` and `CMakeUserPresets.json`, that allow users to 
specify common configure, build, and test options and share them with others. For more
information see [cmake-presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html).

### CCache on Linux

To use, e.g. [CCache (a fast C/C++ compiler cache)](https://ccache.dev/) for CMake's configure 
phase, write your own `CMakeUserPresets.json` using e.g. GNU compiler with

```json
{
    "version": 8,
    "include": [
        "cmake/presets/common.json"
    ], 
    "configurePresets": [
        {
            "name": "gcc-ccache",
            "displayName": "GnuC (CCache)",
            "description": "GnuC compiler using compiler (CCache)",
            "inherits": [
                "gcc",
                "ccache"
            ]
        }
    ],
    "buildPresets": [
        {
            "name": "gcc-ccache-release",
            "displayName": "Release",
            "description": "Release build with GnuC",
            "configuration": "Release",
            "configurePreset": "gcc-ccache"
        }
    ],
    "testPresets": [
        {
            "name": "gcc-ccache-release-test",
            "displayName": "Release Test",
            "description": "Test GnuC build",
            "configuration": "Release",
            "configurePreset": "gcc-ccache",
            "inherits": [
                "default-testPreset"
            ]
        }
    ],
    "workflowPresets": [
        {
            "name": "GnuC Release (CCache)",
            "displayName": "CI GnuC Release (CCache)",
            "description": "Continuous Integration/Continuous Delivery using GnUC (Release)",
            "steps": [
                {
                    "type": "configure",
                    "name": "gcc-ccache"
                },
                {
                    "type": "build",
                    "name": "gcc-ccache-release"
                },
                {
                    "type": "test",
                    "name": "gcc-ccache-release-test"
                }
            ]
        }
    ]
}
```

The [`cmake/presets/common.json`](../cmake/presets/common.json) presets already 
contains a predefined "ccache" section:

```json
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

Also, there are some already pre-configured user CMake presets below 
[`cmake/presets/user`](/cmake/presets/user). Simply copy one of your
choice to `${source_dir}` as `CMakeUserPresets.json` - this file
is excluded from *git*, see [`.gitignore`](../.gitignore).

You can check the use of PCH with given `-H` argument, see SO
[How do I check if precompiled headers are really used?](
https://stackoverflow.com/questions/77838811/how-do-i-check-if-precompiled-headers-are-really-used)

> **ToDo** See Clang Issue [Ccache clang and `-fno-pch-timestamp`](https://discourse.cmake.org/t/ccache-clang-and-fno-pch-timestamp/7253)

### MSVC and sccache

Following [SCCache Usage](https://github.com/mozilla/sccache?tab=readme-ov-file#usage) for
MSVC and CMake 3.25 and later, you have to use the new `CMAKE_MSVC_DEBUG_INFORMATION_FORMAT` option,
meant to configure the `-Z7` flag. Additionally, you must set the cmake policy number 
[CMP0141](https://cmake.org/cmake/help/latest/policy/CMP0141.html) to the `NEW` setting.

```json
        {
            "name": "sccache",
            "description": "sccache - Mozilla's ccache-like tool",
            "hidden": true,
            "cacheVariables": {
                "CMAKE_CXX_COMPILER_LAUNCHER": "sccache",
                "CMAKE_MSVC_DEBUG_INFORMATION_FORMAT": "Embedded",
                "CMAKE_POLICY_DEFAULT_CMP0141": "NEW"                
            }
        },
```

> **ToDo** See Issue [MSVC: /FC, and /Fp "Non-cacheable reasons #978](
https://github.com/mozilla/sccache/issues/978), so we can have pre-compiled header or
sccache.

## Linting: Clang Tidy

The [.clang-tidy](../.clang-tidy) config file applies some checks and disabled others.

### Disabled checks:

There are disabled checks which shouldn't be. Enabling this checks requires more effort:

- [misc-no-recursion](https://clang.llvm.org/extra/clang-tidy/checks/misc-no-recursion.html):
  *Until the ast_printer recursive call chain has been solved.*

- [cppcoreguidelines-pro-bounds-array-to-pointer-decay](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-bounds-array-to-pointer-decay.html):
  *Ignored at this time. With C++20 we get [std::span](https://en.cppreference.com/w/cpp/container/span)
   aka gsl::span aka gsl:: gsl::array_view.* But Boost Spirit.X3 or even Boost.parser must support
   this too.

- [readability-identifier-naming](https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html)
  *Here a lot of effort is required to consolidate and unify all the naming*, e.g. see
  [.clang-tidy](https://github.com/xournalpp/xournalpp/blob/master/.clang-tidy) or
  [.clang-tidy](https://github.com/ROCmSoftwarePlatform/AMDMIGraphX/blob/develop/.clang-tidy) as example.

### Permanently disabled checks:

- [modernize-use-trailing-return-type](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-trailing-return-type.html):
  *This transformation is purely stylistic. We are not quite that modern.*

- [modernize-use-nodiscard](https://clang.llvm.org/extra/clang-tidy/checks/modernize-use-nodiscard.html):
  *This would affect a lot of value returning member functions everywhere and doesn't give any additional information.*

- [readability-redundant-access-specifiers](https://clang.llvm.org/extra/clang-tidy/checks/readability-redundant-access-specifiers.html):
  *This is correct, but is used here for classification purposes.*

- [cppcoreguidelines-pro-type-vararg](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines-pro-type-vararg.html):
  *By using Boost UTF this rule is triggered on each BOOST_TEST macros. No c-style vararg functions are written in this project.*

## Formatting: Clang-Format

The source format is given by Clang-Format's configuration [.clang-format](../.clang-format), or
even simpler by [EditorConfig](https://editorconfig.org/)'s [.editorconfig](../.editorconfig).
