/*
 * user_home.cpp
 *
 *  Created on: 10.08.2018
 *      Author: olaf
 */

#include <eda/util/file/user_home.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <eda/util/cxx_bug_fatal.hpp>

#include <eda/namespace_alias.hpp>

#include <iostream>


namespace eda { namespace util {


/*
 * FixMe: small source code, maybe better move to ibis::init() ???
 */
fs::path user_home(std::initializer_list<char const*> path_list)
{
    const char *HOME_ENV
#if BOOST_OS_LINUX
    = { std::getenv("HOME") };
#elif BOOST_OS_WINDOWS
    = { std::getenv("USERPROFILE") };
#else
#error "No source for getting HOME directory on your platform"
#endif

    if (cxx_expect_not( !HOME_ENV )) {
        throw std::runtime_error("No viable environment variable for user's home.");
    }

    fs::path path{ HOME_ENV };

    boost::system::error_code ec;

    // The HOME directory must exist and must be a directory

    /*
     * XXX ToDo: make own/special exception classes
     */
    if (cxx_expect_not( !fs::exists(path, ec) )) {
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    if (cxx_expect_not( !fs::is_directory(path, ec) )){
        throw std::runtime_error("Fatal: " + path.make_preferred().string() + ": " + ec.message());
    }

    for (auto dir : path_list) {
        path /= dir;
    }

    return path;
}


} } // namespace eda.util



