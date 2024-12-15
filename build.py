import os, shutil, subprocess

def run(cmd):
    os.system(cmd)

try:
    shutil.rmtree("build")
except:
    pass

run("python3 conan_install.py --profile gcc")
#run("cmake --list-presets")
#run('cmake --preset "gcc-ccache"')
#run('cmake --build --preset "gcc-ccache-release"')
run('cmake --workflow --preset "GnuC Release (CCache)"')
