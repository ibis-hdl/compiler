/*
 * type.hpp
 *
 *  Created on: 30.05.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_TYPE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_TYPE_HPP_


#include <cstdint>
#include <type_traits>


namespace eda { namespace vhdl { namespace intrinsic {


/*
 * Integer and Real Types used in VHDL
 *
 * Note: On Linux/Clang 5, the std::int_fast32_t has 64 bit
 */

using signed_integer_type = std::int_fast64_t;
using unsigned_integer_type = std::make_unsigned<signed_integer_type>::type;
using real_type = double;


} } } // namespace eda.vhdl.intrinsic


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_TYPE_HPP_ */
