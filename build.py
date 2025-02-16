#!/usr/bin/env python3

import os, shutil, subprocess

def run(cmd):
    os.system(cmd)

def cleanup():
    # remove build folder
    try:
        shutil.rmtree("build")
    except:
        pass
    # remove ConanCMakePresets.json
    try:
        shutil.rmtree("ConanCMakePresets.json")
    except:
        pass
    

def gcc_release():
    run("python3 conan_install.py --profile gcc --build-type Release")
    run("cmake --preset gcc")
    run("cmake --build --preset gcc-release")
    run("ctest --preset gcc-release-test")

def clang_release():
    run("python3 conan_install.py --profile clang --build-type Release")
    run("cmake --preset clang")
    run("cmake --build --preset clang-release")
    run("ctest --preset clang-release-test")

def clang_libcxx_release():
    run("python3 conan_install.py --profile clang-libc++ --build-type Release")
    run("cmake --preset clang-libc++")
    run("cmake --build --preset clang-libc++-release")
    run("ctest --preset clang-libc++-release-test")

def dev_clang():
    # FixMe: compiles with NDEBUG, dev flags missing!!
    run("python3 conan_install.py --profile clang --build-type Debug")
    run("cmake --preset dev-clang")
    run("cmake --build --preset dev-clang-build")
    run("ctest --preset dev-clang-build-test")

#def asan_test():
#    run("python3 conan_install.py --profile clang --build-type Debug")
#    #run("cmake --list-presets")
#    run("cmake --preset dev-clang-asan")
#    run("cmake --build --preset dev-clang-asan-build | tee build.log")


cleanup()
run("cmake --list-presets")
#gcc_release()
#clang_release()
#clang_libcxx_release()
dev_clang()

