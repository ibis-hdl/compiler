/*
 * overloaded.hpp
 *
 *  Created on: 27.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SUPPORT_CXX_OVERLOADED_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SUPPORT_CXX_OVERLOADED_HPP_


namespace eda { namespace util {


// until we get this in C++20 we have here our own overload
// \see https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


} } // namespace eda.util


#endif /* SOURCES_COMMON_INCLUDE_EDA_SUPPORT_CXX_OVERLOADED_HPP_ */
