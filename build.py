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
run("python3 conan_install.py --profile gcc")
#run("cmake --list-presets")
#run('cmake --preset "gcc-ccache"')
#run('cmake --build --preset "gcc-ccache-release"')
run('cmake --workflow --preset "GnuC Release (CCache)"')
