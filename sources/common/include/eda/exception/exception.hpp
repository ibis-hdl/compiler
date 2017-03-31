/*
 * exception.hpp
 *
 *  Created on: 19.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_EXCEPTION_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_EXCEPTION_HPP_


#include <stdexcept>

#include <boost/exception/exception.hpp>
#include <boost/exception/error_info.hpp>


namespace eda {


/**
 * This class defines the type of objects thrown as exceptions to report range
 * errors in internal computations.
 */
struct range_error : public boost::exception, public std::range_error
{
    using std::range_error::range_error;
};

using range_error_min = boost::error_info<struct tag_int32_range_min, int32_t>;
using range_error_max = boost::error_info<struct tag_int32_range_max, int32_t>;


} // namespace eda


#endif /* SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_EXCEPTION_HPP_ */
