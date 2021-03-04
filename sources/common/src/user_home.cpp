/*
 * user_home.cpp
 *
 *  Created on: 10.08.2018
 *      Author: olaf
 */

#include <eda/util/file/user_home_dir.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/system/error_code.hpp>

#include <eda/namespace_alias.hpp> // IWYU pragma: keep
#include <eda/compiler/compiler_support.hpp> // IWYU pragma: keep
#include <eda/platform.hpp>

#include <cstdlib>
#include <stdexcept>
#include <string>

namespace eda {
namespace util {

/*
 * FixMe: small source code, maybe better move to ibis::init() ???
 *
 * On Windows use [SHGetKnownFolderPath function](
 * https://docs.microsoft.com/en-us/windows/desktop/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath)
 * with example given at [SO](
 * https://stackoverflow.com/questions/24124851/getenvironmentvariablea-usage)
 * to avoid warnings from MSVC.
 */
fs::path user_home_dir(std::initializer_list<char const*> path_list)
{
    std::string const HOME_ENV = []() {
        if constexpr (eda::build_platform == platform::Unix) {
            return std::getenv("HOME");
        }
        else if constexpr (eda::build_platform == platform::Win32) {
            return std::getenv("USERPROFILE");
        }
        else {
            // FixMe: hopefully, this will be correct, static_assert doesn't work here
            throw std::runtime_error("Platform support bug: It's not Unix or Win32.");
            //return std::getenv("HOME");
        }
    }();

    // FixMe: throwing exceptions should not be a viable solution here ...

    if (HOME_ENV.empty()) {
        throw std::runtime_error("No viable environment variable for user's home.");
    }

    fs::path path{ HOME_ENV };

    boost::system::error_code ec;

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

} // namespace util
} // namespace eda
