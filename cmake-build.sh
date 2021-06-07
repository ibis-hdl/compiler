#!/usr/bin/env bash

# Use English to make copy&paste of errors easier to
# open reports in forums
LANG=en_US.UTF-8

# http://mywiki.wooledge.org/BashFAQ/028
SCRIPT_PATH="$( cd "$(dirname "$0")" ; pwd -P )"

# this script is in the same directory
MY_SOURCE_DIR="${SCRIPT_PATH}"
MY_BUILD_DIR="$(cd "$(dirname "$PWD")" ; pwd -P )/build"

CMAKE_CXX_COMPILER=clang++
CMAKE_GENERATOR="Ninja"
CMAKE_BIN="$(which cmake)"

# Debug, Release, RelWithDebInfo, MinSizeRel
CMAKE_BUILD_TYPE=Release

cat << EOF
##
## Configure:
##
## Source directory: ${MY_SOURCE_DIR}
## Build directoy:   ${MY_BUILD_DIR}
## Build type:       ${CMAKE_BUILD_TYPE}
## Build generator:  ${CMAKE_GENERATOR}
## Compiler:         ${CMAKE_CXX_COMPILER}
##
EOF

${CMAKE_BIN} -E make_directory ${MY_BUILD_DIR}

cd ${MY_BUILD_DIR}

# [IWYU could not find stddef.h on Ubuntu 18.04](
#  https://github.com/include-what-you-use/include-what-you-use/issues/679)
# enable this to setup system include path for iwyu if required
#export CXXFLAGS="-isystem /usr/lib64/clang/11.0.0/include/"

${CMAKE_BIN} --trace-expand \
        ${MY_SOURCE_DIR} \
        -G "${CMAKE_GENERATOR}" \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} \
        -DCMAKE_INSTALL_PREFIX=stage \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        2> cmake.out


# cleanup before the run cmake
${CMAKE_BIN} --build ${MY_BUILD_DIR} --target clean

# make && build
#${CMAKE_BIN} --build ${MY_BUILD_DIR} --target all --config ${CMAKE_BUILD_TYPE}
