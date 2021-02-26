#!/usr/bin/env bash

# Use English to make copy&paste of errors easier to 
# open reports in forums
LANG=en_US.UTF-8

# http://mywiki.wooledge.org/BashFAQ/028
SCRIPT_PATH="$( cd "$(dirname "$0")" ; pwd -P )"

# this script is in the same directory
EDA_SOURCE_DIR="${SCRIPT_PATH}"
EDA_BUILD_DIR="${EDA_SOURCE_DIR}/../build"

CMAKE_BIN="$(which cmake)"
CMAKE_GENERATOR="Eclipse CDT4 - Unix Makefiles"

# Debug, Release, RelWithDebInfo, MinSizeRel
CMAKE_BUILD_TYPE=RelWithDebInfo

CXX_COMPILER=clang++

CPU_COUNT=$(grep ^processor /proc/cpuinfo | wc -l)
CPU_COUNT=1 # override for low end computer


cat << EOF
##
## Configure CMake Eclipse Build
##
## Source directory: ${EDA_SOURCE_DIR}
## Build directoy:   ${EDA_BUILD_DIR} 
## Build type:       ${CMAKE_BUILD_TYPE}
## Compiler:         ${CXX_COMPILER}
##
EOF

${CMAKE_BIN} -E make_directory ${EDA_BUILD_DIR}

cd ${EDA_BUILD_DIR}

${CMAKE_BIN} ${EDA_SOURCE_DIR} \
        -G "${CMAKE_GENERATOR}" \
        -DCMAKE_ECLIPSE_VERSION=4.6 \
        -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
        -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j${CPU_COUNT} \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
        -DCMAKE_CXX_COMPILER=${CXX_COMPILER} \
        -DCMAKE_RULE_MESSAGES:BOOL=OFF \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
        -DCMAKE_INSTALL_PREFIX=stage \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	 
# cleanup before the run cmake
${CMAKE_BIN} --build ${EDA_BUILD_DIR} --target clean
# make && build
${CMAKE_BIN} --build ${EDA_BUILD_DIR} --target all --config ${CMAKE_BUILD_TYPE}
