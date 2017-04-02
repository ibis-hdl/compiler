/*
 * cxx_bug_fatal.hpp
 *
 *  Created on: 19.03.2017
 *      Author: olaf
 */

#ifndef INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_
#define INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_


#include <eda/utils/compiler_support.hpp>

#include <cstdlib>
#include <iostream>


namespace eda { namespace utils { namespace detail {


template <typename CharT>
void assertion_failed_msg(const CharT* expr, const char* msg, const char* function, const char* file, long line) {
    std::cerr
        << "\n****************************************\n"
        <<   "***** Internal Fatal Program Error *****\n"
        <<   "****************************************\n"
        << "assertion (" << expr << ") failed in "
        << function << ":\n"
        << file << '(' << line << "): " << msg << std::endl;
    std::quick_exit(EXIT_FAILURE);
}

} } } // namespace eda.utils.detail




#define cxx_assert(condition, message) \
    (cxx_expect(condition) \
    ? ((void)0)            \
    : ::eda::utils::detail::assertion_failed_msg(#condition, message, \
       __PRETTY_FUNCTION__, __FILE__, __LINE__))



#define cxx_bug_fatal(message) \
    cxx_assert(false, message);  \
    cxx_unreachable(message);



#endif /* INCLUDE_EDA_UTILS_CXX_BUG_FATAL_HPP_ */
