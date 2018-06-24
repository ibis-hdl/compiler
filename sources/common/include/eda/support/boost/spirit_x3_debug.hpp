/*
 * spirit_x3_debug.hpp
 *
 *  Created on: 21.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_DEBUG_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_DEBUG_HPP_


/* Note, intended to be used with defined BOOST_SPIRIT_X3_DEBUG
 * After Spirit.X3 1.64 the code with defined BOOST_SPIRIT_X3_DEBUG seems to be
 * changed. Old support for the AST nodes using operator<<() isn't required
 * any more, but the code for x3::raw[] / boost::iterator_range<> is missing,
 * hence Quick&Dirty to supply this. */
namespace boost { namespace spirit { namespace x3 { namespace traits
{
    template <typename Out, typename T>
    inline void print_attribute(Out& os, boost::iterator_range<T> const& range) {
        os << range;
    }

}}}}


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_DEBUG_HPP_ */