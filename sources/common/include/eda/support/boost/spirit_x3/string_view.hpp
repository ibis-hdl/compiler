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


namespace boost { namespace spirit { namespace x3 { namespace traits {


template <typename It>
void move_to(It b, It e, std::string_view& v)
{
    /* see [parsing from std::string into a boost::string_view using boost::spirit::x3]
     * (https://stackoverflow.com/questions/39225502/parsing-from-stdstring-into-a-booststring-view-using-boostspiritx3)
     * Note storage is contiguous, use concept check for input range */
    v = std::string_view(&*b, std::size_t(e - b));
}


} } } } // namespace boost.spirit.x3.traits


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_STRING_VIEW_HPP_ */
