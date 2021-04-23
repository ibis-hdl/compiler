#pragma once

#include <cstdint>
#include <type_traits>

namespace ibis::vhdl::intrinsic {

///
/// Universal Integer and Real Types used in VHDL
///
/// Note: On Linux/Clang 5, the std::int_fast32_t has 64 bit
///

using signed_integer_type = std::int_fast64_t;
using unsigned_integer_type = std::make_unsigned<signed_integer_type>::type;
using real_type = double;

}  // namespace ibis::vhdl::intrinsic
