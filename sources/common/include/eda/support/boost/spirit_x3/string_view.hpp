/*
 * string_view.hpp
 *
 *  Created on: 13.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_STRING_VIEW_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_STRING_VIEW_HPP_


#include <experimental/string_view>


/* nevertheless import string_view into namespace std until C++17 compilers
 * are used here. Note, on conforming C++17 compilers, e.g. gcc-7.1,
 * problems with move_to will rise! */
namespace std {
    using string_view = std::experimental::string_view;
}


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_STRING_VIEW_HPP_ */
