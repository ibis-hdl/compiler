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
    
cleanup()
run("python3 conan_install.py --profile clang --build-type Debug")
#run("cmake --list-presets")
run("cmake --preset dev-clang-iwyu")
run("cmake --build --preset dev-clang-iwyu-build | tee build-iwyu.log")

