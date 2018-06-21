/*
 * spirit_x3.hpp
 *
 *  Created on: 30.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_


/* special boost.spirit.x3 header to get rid off the annoying unused parameter
 * warnings from x3 */
#include <eda/utils/compiler_push.hpp>
#include <eda/utils/compiler_warning.hpp>

#if defined(BOOST_SPIRIT_X3_DEBUG)
#include <eda/support/boost/spirit_x3_debug.hpp>
#endif

#include <boost/spirit/home/x3.hpp>

#include <eda/utils/compiler_pop.hpp>


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_ */
