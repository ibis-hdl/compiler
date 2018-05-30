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

typedef std::int_fast64_t                               signed_integer_type;
typedef std::make_unsigned<signed_integer_type>::type   unsigned_integer_type;


} } } // namespace eda.vhdl.intrinsic


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_TYPE_HPP_ */
