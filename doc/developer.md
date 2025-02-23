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
