#!/usr/bin/env bash

echo 1>&2 "logging include-what-you-use call by cmake: " "$@"
exec include-what-you-use "$@"
