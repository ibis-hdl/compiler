#!/bin/bash

set -ex

pip3 --disable-pip-version-check --no-cache-dir install conan
conan profile new --detect --force default > /dev/null
# Conan detects a GCC version > 5 but has adjusted the 'compiler.libcxx' setting to
# 'libstdc++' for backwards compatibility. Our compiler is using the new CXX11 ABI 
# by default (libstdc++11).
conan profile update settings.compiler.libcxx=libstdc++11 default
# C++20 standard
conan profile update settings.compiler.std=20 default
