#/usr/bin/env bash

SCRIPT_PATH="${BASH_SOURCE%/*}"

IWYU_BIN=$(which include-what-you-use)
IWYU_COMMENT="-Xiwyu;--no_comments"
#IWYU_COMMENT="-Xiwyu;--max_line_length=160"
IWYU_MAP="${PWD}/${SCRIPT_PATH}/misc_iwyu.imp"

cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE="${IWYU_BIN};-Xiwyu;--transitive_includes_only;${IWYU_COMMENT};${IWYU_MAP}" @CMAKE_SOURCE_DIR@
