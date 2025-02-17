#!/usr/bin/env python3

import os, shutil, subprocess

def run(cmd):
    print(f"RUNNING: '{cmd}':")
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
    
def workflow_release(conan_profile : str, cmake_base_preset: str):
    run(f"python3 conan_install.py --profile {conan_profile} --build-type Release")
    run(f"cmake --preset {cmake_base_preset}")
    run(f"cmake --build --preset {cmake_base_preset}-release")
    run(f"ctest --preset {cmake_base_preset}-release-test")

def workflow_dev(conan_profile : str, cmake_base_preset: str, build_type : str, ctest : bool = False):
    run(f"python3 conan_install.py --profile {conan_profile} --build-type {build_type}")
    run(f"cmake --preset {cmake_base_preset}")
    run(f"cmake --build --preset {cmake_base_preset}-build -j1")
    if ctest:
        run(f"ctest --preset {cmake_base_preset}-build-test")

def gcc_release():
    conan_profile = "gcc"
    cmake_base_preset = "gcc"
    workflow_release(conan_profile, cmake_base_preset)

def clang_release():
    conan_profile = "clang"
    cmake_base_preset = "clang"
    workflow_release(conan_profile, cmake_base_preset)

def clang_libcxx_release():
    conan_profile = "clang-libc++"
    cmake_base_preset = "clang-libc++"
    workflow_release(conan_profile, cmake_base_preset)

def dev_clang():
    conan_profile = "clang"
    cmake_base_preset = "dev-clang"
    build_type = "Debug"
    workflow_dev(conan_profile, cmake_base_preset, build_type)

def dev_clang_iwyu():
    conan_profile = "clang"
    cmake_base_preset = "dev-clang-iwyu"
    build_type = "Debug"
    workflow_dev(conan_profile, cmake_base_preset, build_type)


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
#dev_clang()
dev_clang_iwyu()            # ./build.py 2>&1 | tee -a build-iwyu.log

