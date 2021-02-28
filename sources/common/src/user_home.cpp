/*
 * user_home.cpp
 *
 *  Created on: 10.08.2018
 *      Author: olaf
 */

#include <eda/util/file/user_home_dir.hpp>

#include <eda/compiler/compiler_support.hpp> // IWYU pragma: keep
#include <eda/namespace_alias.hpp> // IWYU pragma: keep

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/predef/os/linux.h>
#include <boost/system/error_code.hpp>

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
    const char* HOME_ENV
#if BOOST_OS_LINUX
        = { std::getenv("HOME") };
#elif BOOST_OS_WINDOWS
        = { std::getenv("USERPROFILE") };
#else
#error "No source for getting HOME directory on your platform"
#endif

    if (cxx_expect_not(!HOME_ENV)) {
        throw std::runtime_error("No viable environment variable for user's home.");
    }

    fs::path path{ HOME_ENV };

    boost::system::error_code ec;

    // The HOME directory must exist and must be a directory

    if (cxx_expect_not(!fs::exists(path, ec))) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    if (cxx_expect_not(!fs::is_directory(path, ec))) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    for (const auto *const dir : path_list) {
        path /= dir;
    }

    return path;
}

} // namespace util
} // namespace eda
