/*
 * user_home.hpp
 *
 *  Created on: 10.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_USER_HOME_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_USER_HOME_HPP_

#include <initializer_list>

namespace boost {
namespace filesystem {

// forward
class path;

} // namespace filesystem
} // namespace boost

namespace eda {
namespace util {

boost::filesystem::path user_home(std::initializer_list<char const*> path_list);
}
} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_UTIL_FILE_USER_HOME_HPP_ */
