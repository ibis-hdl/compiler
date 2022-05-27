#!/usr/bin/env bash

set -ex

# using docker volumes to store data, fix permissions
# ToDo: solve this problem with correct configurations using e.g. by JSON
if [ ! -d "/home/vscode/.conan" ]; then
    sudo mkdir /home/vscode/.conan && chown -R vscode.vscode /home/vscode/.conan
elif [ $(stat --format '%U' "/home/vscode/.conan") = "root" ]; then
    echo "fix permissions for conan"
    sudo chown -R vscode.vscode /home/vscode/.conan
fi

if [ ! -d "/home/vscode/.cache" ]; then
    sudo mkdir /home/vscode/.cache && chown -R vscode.vscode /home/vscode/.cache
elif [ $(stat --format '%U' "/home/vscode/.cache") = "root" ]; then
    echo "fix permissions for ccache"
    sudo chown -R vscode.vscode /home/vscode/.cache
fi

pip3 --disable-pip-version-check --no-cache-dir install wheel conan
conan profile new --detect --force default > /dev/null
# Conan detects a GCC version > 5 but has adjusted the 'compiler.libcxx' setting to
# 'libstdc++' for backwards compatibility. Our compiler is using the new CXX11 ABI
# by default (libstdc++11).
conan profile update settings.compiler.libcxx=libstdc++11 default
# C++20 standard
conan profile update settings.compiler.cppstd=20 default
