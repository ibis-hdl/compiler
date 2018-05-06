/*
 * spirit_x3.hpp
 *
 *  Created on: 30.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_


/* special boost.spirit.x3 header to get rid off the annoying unused parameter
 * warnings from x3 introduced later on boost libs 1.60 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <boost/spirit/home/x3.hpp>

#pragma GCC diagnostic pop


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_BOOST_SPIRIT_X3_HPP_ */
