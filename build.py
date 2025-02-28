#!/usr/bin/env python3

import os, sys, shutil, subprocess

def run(cmd):
    print(f"##### Build Script Running: '{cmd}' #####", file=sys.stderr)
    os.system(cmd)

def cleanup():
    try:  # remove build folder
        shutil.rmtree("build")
    except:
        pass
    try:  # remove ConanCMakePresets.json
        shutil.rmtree("ConanCMakePresets.json")
    except:
        pass

def workflow(conan_profile : str, cmake_conf_preset: str, build_type : str, preset_sfx : str, jobs: int, ctest : bool):
    cleanup()
    run(f"python3 conan_install.py --profile {conan_profile} --build-type {build_type}")
    run(f"cmake --preset {cmake_conf_preset}")
    run(f"cmake --build --preset {cmake_conf_preset}-{preset_sfx} -j{jobs}")
    if ctest:
        run(f"ctest --preset {cmake_conf_preset}-{preset_sfx}-test")

def workflow_release(conan_profile : str, cmake_conf_preset: str, jobs: int = 34, ctest : bool = True):
    workflow(conan_profile, cmake_conf_preset, "Release", "release", jobs, True)

def workflow_dev(conan_profile : str, cmake_conf_preset: str, build_type : str, jobs: int = 34, ctest : bool = False):
    workflow(conan_profile, cmake_conf_preset, build_type, "build", jobs, False)

def gcc_release():
    conan_profile = "gcc"
    cmake_conf_preset = "gcc"
    jobs = os.cpu_count()
    workflow_release(conan_profile, cmake_conf_preset, jobs)

def clang_release():
    conan_profile = "clang"
    cmake_conf_preset = "clang"
    jobs = os.cpu_count()
    workflow_release(conan_profile, cmake_conf_preset, jobs)

def clang_libcxx_release():
    conan_profile = "clang-libc++"
    cmake_conf_preset = "clang-libc++"
    jobs = os.cpu_count()
    workflow_release(conan_profile, cmake_conf_preset, jobs)

def dev_clang():
    conan_profile = "clang"
    cmake_conf_preset = "dev-clang"
    build_type = "Debug"
    jobs = os.cpu_count()
    workflow_dev(conan_profile, cmake_conf_preset, build_type, jobs)

def dev_clang_tidy():
    conan_profile = "clang"
    cmake_conf_preset = "dev-clang-tidy"
    build_type = "Release"
    jobs = os.cpu_count()
    workflow_dev(conan_profile, cmake_conf_preset, build_type, jobs)

def dev_clang_iwyu():
    # ToDo Doesn't work as expected
    conan_profile = "clang"
    cmake_conf_preset = "dev-clang-iwyu"
    build_type = "Release"
    jobs = os.cpu_count()
    workflow_dev(conan_profile, cmake_conf_preset, build_type, jobs)

def dev_gcc_iwyu():
    conan_profile = "gcc"
    cmake_conf_preset = "dev-gcc-iwyu"
    build_type = "Release"
    jobs = os.cpu_count()
    workflow_dev(conan_profile, cmake_conf_preset, build_type, jobs)

def dev_clang_asan():
    # ToDo Doesn't work as expected
    conan_profile = "clang"
    cmake_conf_preset = "dev-clang-asan"
    build_type = "Debug"
    jobs = os.cpu_count()
    workflow_dev(conan_profile, cmake_conf_preset, build_type, jobs)

run("cmake --list-presets")
#gcc_release()
#clang_release()
#clang_libcxx_release()
#dev_clang()
dev_clang_tidy()
#dev_clang_iwyu()
#dev_gcc_iwyu()
#dev_clang_asan()


# ./build.py 2>&1 | tee build-script.log
