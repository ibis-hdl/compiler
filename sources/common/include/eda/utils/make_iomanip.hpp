/*
 * make_iomanip.hpp
 *
 *  Created on: 28.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_UTILS_MAKE_IOMANIP_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_UTILS_MAKE_IOMANIP_HPP_


#include <type_traits>
#include <iostream>


namespace eda { namespace utils {


/**
 * Helper to make a 'streamable' C++ lambda function
 *
 * Example:
 * \code{.cpp}
 * auto const answer = [](size_t count) {
 *    return make_iomanip([count](std::ostream& os) {
 *         if(count) {
 *            os << "The answer is " << count;
 *        }
 *    });
 * };
 * ...
 * std::cout << answer(42) << std::endl;
 * \endcode
 *
 * Based on yazmir8azyr from IRC ##c++ channel, see [WandBox.Org](
 * https://wandbox.org/permlink/wGDqfmxCKwqob5mp)
 */
template <typename T>
struct A
{
    T x;

    friend std::ostream& operator<<(std::ostream& os, A a) {
        a.x(os);
        return os;
     }
};


template <typename T>
A<std::decay_t<T>> make_iomanip(T&& x) {
    return { std::forward<T>(x) };
}


} } // namespace eda.utils


#endif /* SOURCES_COMMON_INCLUDE_EDA_UTILS_MAKE_IOMANIP_HPP_ */
