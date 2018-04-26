/*
 * assert_failure.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_ASSERT_FAILURE_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_ASSERT_FAILURE_HPP_


#include <stdexcept>

#include <boost/exception/exception.hpp>
#include <boost/exception/error_info.hpp>

#include <eda/utils/compiler_support.hpp>


namespace eda {


/**
 *
 * \see http://ericniebler.com/2014/09/27/assert-and-constexpr-in-cxx11/
 * \see https://github.com/wichtounet/cpp_utils/blob/master/assert.hpp
 * \see https://github.com/boostorg/assert/blob/develop/include/boost/assert.hpp
 *
 * \todo Throwing assert rework
 */
struct assert_failure : public boost::exception, public std::logic_error
{
    explicit assert_failure(std::string const& message)
    : std::logic_error(message)
    {
        std::cerr << "Assertion failure: %s\n";

#if defined(EDA_HAVE_STD_QUICK_EXIT)
        std::quick_exit(EXIT_FAILURE);
#else
        std::exit(EXIT_FAILURE);
#endif
    }
};


} // namespace eda





#endif /* SOURCES_COMMON_INCLUDE_EDA_EXCEPTION_ASSERT_FAILURE_HPP_ */
