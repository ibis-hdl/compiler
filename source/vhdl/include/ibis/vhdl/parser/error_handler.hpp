#pragma once

#include <ibis/vhdl/error_handler.hpp>

namespace ibis::vhdl::parser {

///
/// tag used to get our error handler from the x3::context
///
struct error_handler_tag;  // IWYU pragma: keep

///
/// Parser error handler
///
template <typename Iterator>
using error_handler = vhdl::error_handler<Iterator>;

}  // namespace ibis::vhdl::parser
