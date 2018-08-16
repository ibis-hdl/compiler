#!/usr/bin/env bash

# http://mywiki.wooledge.org/BashFAQ/028
SCRIPT_PATH="$( cd "$(dirname "$0")" ; pwd -P )"

# this script is in the same directory
EDA_SOURCE_DIR="${SCRIPT_PATH}"
EDA_BUILD_DIR="${EDA_SOURCE_DIR}/../build"

CMAKE_BIN="$(which cmake)"
CMAKE_GENERATOR="Eclipse CDT4 - Ninja"

# Debug, Release, RelWithDebInfo, MinSizeRel
CMAKE_BUILD_TYPE=RelWithDebInfo

cat << EOF
##
## Configure from Source ${EDA_SOURCE_DIR}
## Build in ${EDA_BUILD_DIR} 
## ${CMAKE_BUILD_TYPE}
##
EOF

${CMAKE_BIN} -E make_directory ${EDA_BUILD_DIR}

LANG=en_US.UTF-8

cd ${EDA_BUILD_DIR}

${CMAKE_BIN} -G "${CMAKE_GENERATOR}" \
        -DCMAKE_ECLIPSE_VERSION=4.6 \
        -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
        -DCMAKE_RULE_MESSAGES:BOOL=OFF \
        -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON \
        -DCMAKE_INSTALL_PREFIX=stage \
        -DBUILD_SHARED_LIBS:BOOL=OFF \
	 ${EDA_SOURCE_DIR}

${CMAKE_BIN} --build ${EDA_BUILD_DIR} --target all --config ${CMAKE_BUILD_TYPE}