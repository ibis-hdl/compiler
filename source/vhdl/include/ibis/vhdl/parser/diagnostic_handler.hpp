#pragma once

#include <ibis/vhdl/diagnostic_handler.hpp>

namespace ibis::vhdl::parser {

///
/// tag used to get our error handler from the x3::context
///
struct diagnostic_handler_tag;  // IWYU pragma: keep

///
/// Parser error handler
///
template <typename Iterator>
using diagnostic_handler = vhdl::diagnostic_handler<Iterator>;

}  // namespace ibis::vhdl::parser