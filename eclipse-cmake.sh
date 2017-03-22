#!/usr/bin/env bash

# http://mywiki.wooledge.org/BashFAQ/028
SCRIPT_PATH="${BASH_SOURCE%/*}"
cd "${SCRIPT_PATH}" || exit

# this script is in the same directory
EDA_SRC_DIR=${SCRIPT_PATH}

cmake -G "Eclipse CDT4 - Unix Makefiles" \
        -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
        -DCMAKE_ECLIPSE_VERSION=4.6 \
        -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j4 \
        -DCMAKE_RULE_MESSAGES:BOOL=OFF \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_COMPILER=g++ \
        -DCMAKE_INSTALL_PREFIX=stage \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
        ${EDA_SRC_DIR}
        
#cmake --build .
make -j4

