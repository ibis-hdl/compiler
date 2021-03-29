#pragma once

#include <stdexcept>

#include <boost/exception/error_info.hpp>
#include <boost/exception/exception.hpp>

#include <eda/compiler/compiler_support.hpp>

namespace eda {

/**
 *
 * \see http://ericniebler.com/2014/09/27/assert-and-constexpr-in-cxx11/
 * \see https://github.com/wichtounet/cpp_utils/blob/master/assert.hpp
 * \see https://github.com/boostorg/assert/blob/develop/include/boost/assert.hpp
 *
 * \todo Throwing assert rework
 */
struct assert_failure
    : public boost::exception
    , public std::logic_error {
    explicit assert_failure(std::string const& message)
        : std::logic_error{ message }
    {
        std::cerr << "Assertion failure: %s\n";
        std::quick_exit(EXIT_FAILURE);
    }
};

}  // namespace eda
