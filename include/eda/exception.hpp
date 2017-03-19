/*
 * exception.hpp
 *
 *  Created on: 19.03.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_EXCEPTION_HPP_
#define INCLUDE_EDA_EXCEPTION_HPP_


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
    explicit range_error(const std::string& what_arg)
    : std::range_error(what_arg) { }

    explicit range_error(const char* what_arg)
    : std::range_error(what_arg) { }
};

using range_error_min = boost::error_info<struct tag_int32_range_min, int32_t>;
using range_error_max = boost::error_info<struct tag_int32_range_max, int32_t>;


} // namespace eda


#endif /* INCLUDE_EDA_EXCEPTION_HPP_ */
