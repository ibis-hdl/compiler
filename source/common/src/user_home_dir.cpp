//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/util/file/user_home_dir.hpp>

//#include<ibis/util/compiler/compiler_support.hpp> // IWYU pragma: keep
#include <ibis/util/platform.hpp>
//#include<ibis/namespace_alias.hpp>

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <filesystem>
#include <initializer_list>
#include <system_error>

namespace ibis::util {

fs::path user_home_dir(std::initializer_list<char const *> path_list)
{
    std::string const HOME_ENV = []() {
        if constexpr (ibis::platform == platform::Linux) {
            return std::getenv("HOME");
        }
        else if constexpr (ibis::platform == platform::Windows) {
            return std::getenv("USERPROFILE");
        }
        else {
            // FixMe: hopefully, this will be correct, static_assert doesn't work here
            throw std::runtime_error("Platform support bug: It's not Unix or Win32.");
            // return std::getenv("HOME");
        }
    }();

    // FixMe: throwing exceptions should not be a viable solution here ...

    if (HOME_ENV.empty()) {
        throw std::runtime_error("No viable environment variable for user's home.");
    }

    fs::path path{ HOME_ENV };

    std::error_code ec;

    // The HOME directory must exist and must be a directory

    if (!fs::exists(path, ec)) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    if (!fs::is_directory(path, ec)) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    for (const auto *const dir : path_list) {
        path /= dir;
    }

    return path;
}

}  // namespace ibis::util
