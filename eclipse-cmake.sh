#!/usr/bin/env bash

# http://mywiki.wooledge.org/BashFAQ/028
SCRIPT_PATH="${BASH_SOURCE%/*}"

# this script is in the same directory
EDA_SRC_DIR=${SCRIPT_PATH}

CMAKE_BIN=/usr/local/gcc-7.1.0/bin/cmake
CPU_COUNT=$(grep ^processor /proc/cpuinfo | wc -l)
CPU_COUNT=2 # override

${CMAKE_BIN} ${EDA_SRC_DIR} \
		-G "Eclipse CDT4 - Unix Makefiles" \
        -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
        -DCMAKE_ECLIPSE_VERSION=4.6 \
        -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j4 \
        -DCMAKE_RULE_MESSAGES:BOOL=OFF \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_COMPILER=/usr/local/gcc-7.1.0/bin/g++ \
        -DCMAKE_INSTALL_PREFIX=stage \
        -DBUILD_SHARED_LIBS:BOOL=OFF 
        
#cmake --build .
make -j${CPU_COUNT}

