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
 * are used here */
namespace std {
    using string_view = std::experimental::string_view;
}


namespace boost { namespace spirit { namespace x3 { namespace traits {


template <typename It>
void move_to(It b, It e, std::string_view& v)
{
    // Note storage is contiguous, use concept check for input range
    v = std::string_view(&*b, std::size_t(e - b));
}

} } } } // namespace boost.spirit.x3.traits



#include <string>
#include <type_traits>

namespace eda {

static inline
std::string const& to_string(std::string const& str) { return str; }

static inline
std::string& to_string(std::string& str) { return str; }

static inline
std::string to_string(std::string_view const& str) { return str.to_string(); }

static inline
std::string to_string(std::string_view& str) { return str.to_string(); }


} // namespace eda


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_STRING_VIEW_HPP_ */
