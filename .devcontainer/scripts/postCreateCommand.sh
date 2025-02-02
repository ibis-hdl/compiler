#!/usr/bin/env bash

set -ex

# using docker volumes to store data; fix permissions as it's mounted as
# root on Windows/Docker/WSL
# intentionally not recursive, since volumes are mound-bind by docker
apply_dir() {
    local dir=$1

    echo "[DevContainer] INFO: check for '${dir}'"
    if [ ! -d "${dir}" ]; then
        sudo mkdir ${dir} && chown vscode:vscode "${dir}"
    elif [ $(stat --format '%U' "${dir}") = "root" ]; then
        echo "[DevContainer] INFO: fix 'root' permissions for '${dir}'"
        sudo chown vscode:vscode "${dir}"
    fi
}

# using docker volumes to store data; fix permissions as it's mounted as
# root on Windows/Docker/WSL
# intentionally not recursive, since volumes are mound-bind by docker
fix_volume_permissions() {
    # This script is running as user 'vscode'
    echo "[DevContainer] '${0##*/}' runs as user '${SUDO_USER:-$USER}'"

    if [ $(stat --format '%U' "/workspaces") = "root" ]; then
        echo "[DevContainer] INFO: fix 'root' permissions for workspaces folder"
        sudo chown vscode:vscode /workspaces
    fi

    apply_dir "/home/vscode/.conan2"    # not required, but in case of ...
    apply_dir "/home/vscode/.cache"     # not required, but in case of ...
    apply_dir "/home/vscode/.ssh"
}

# update alternatives for llvm.org's clang (unable to do this inside DOckerfile due to write permissions)
set_clang_alternatives() {
    sudo update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-18 18
    sudo update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-19 19
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-18 18
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 19
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 18
    sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-19 19
    sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-19 19
    sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-19 19     
}

fix_volume_permissions
set_clang_alternatives
