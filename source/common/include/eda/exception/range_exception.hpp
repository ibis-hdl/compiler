#pragma once

#include <stdexcept>

#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

namespace eda {

/**
 * This class defines the type of objects thrown as exceptions to report range
 * errors in internal computations.
 */
struct range_error
    : public boost::exception
    , public std::range_error {
    using std::range_error::range_error;
};

using range_error_min = boost::error_info<struct tag_int32_range_min, int32_t>;
using range_error_max = boost::error_info<struct tag_int32_range_max, int32_t>;

}  // namespace eda
