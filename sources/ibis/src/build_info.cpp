/*
 * build_info.cpp
 *
 *  Created on: 06.09.2018
 *      Author: olaf
 */

#include <ibis/build_info.hpp>

#include <boost/version.hpp>
#include <boost/config.hpp>

#include <iostream>

namespace ibis {

void build_info(std::ostream& os)
{
    // clang-format off
    os << "Platform: " << BOOST_PLATFORM << '\n'
       << "Compiler: " << BOOST_COMPILER << '\n'
       << "STL     : " << BOOST_STDLIB   << '\n'
       << "Boost   : " << BOOST_VERSION / 100000 << "."
                       << BOOST_VERSION / 100 % 1000 << "."
                       << BOOST_VERSION % 100
       << std::endl;
    // clang-format on
}

} // namespace ibis

/* FixMe: There are also:
    #cmakedefine BUILD_PLATFORM "@BUILD_PLATFORM@"
    #cmakedefine BUILD_TYPE "@BUILD_TYPE@"
    #cmakedefine BUILD_CFLAGS "@BUILD_CFLAGS@"
    #cmakedefine BUILD_CXXFLAGS "@BUILD_CXXFLAGS@"
    #cmakedefine BUILD_LINKFLAGS "@BUILD_LINKFLAGS@"
    #cmakedefine BUILD_SYSTEM "@BUILD_SYSTEM@"
*/